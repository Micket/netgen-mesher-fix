//
//  Write user dependent output file
//

#include "meshing.hpp"
#include "interface.hpp"

namespace netgen
{

void RegisterUserFormats (Array<const char*> & names)
{
  const char *types[] =
    {
      "Neutral Format",
      "VTU Format",
      "VTU Format, only volume",
      "Surface Mesh Format" ,
      "DIFFPACK Format",
      "TecPlot Format",
      "Tochnog Format",
      "Abaqus Format",
      "Fluent Format",
      "Permas Format",
      "FEAP Format",
      "Elmer Format",
      "STL Format",
      "VRML Format",
      "Gmsh Format",
      "Gmsh2 Format",
      "DOLFIN Format",
      "JCMwave Format",
      "TET Format",
      "Chemnitz Format", // Why not? - Mikael
      0
    };

  for (int i = 0; types[i]; i++)
    names.Append (types[i]);
}



bool WriteUserFormat (const string & format,
		      const Mesh & mesh,
		      const CSGeometry & geom,
		      const string & filename)
{
  PrintMessage (1, "Export mesh to file ", filename,
		", format is ", format);

  if (format == "Neutral Format")
    WriteNeutralFormat (mesh, filename);

  else if (format == "Surface Mesh Format")
    WriteSurfaceFormat (mesh, filename);

  else if (format == "DIFFPACK Format")
    WriteDiffPackFormat (mesh, filename);

  else if (format == "Tochnog Format")
    WriteTochnogFormat (mesh, filename);

  else if (format == "TecPlot Format")
    cerr << "ERROR: TecPlot format currently out of order" << endl;
      // WriteTecPlotFormat (mesh, geom, filename);

  else if (format == "Abaqus Format")
    WriteAbaqusFormat (mesh, filename);

  else if (format == "Fluent Format")
    WriteFluentFormat (mesh, filename);

  else if (format == "Permas Format")
    WritePermasFormat (mesh, filename);

  else if (format == "FEAP Format")
    WriteFEAPFormat (mesh, filename);

  else if (format == "Elmer Format")
    WriteElmerFormat (mesh, filename);

  else if (format == "STL Format")
    WriteSTLFormat (mesh, filename);

  else if (format == "VRML Format")
    WriteVRMLFormat (mesh, 1, filename);

  else if (format == "Fepp Format")
    WriteFEPPFormat (mesh, geom, filename);

  else if (format ==  "EdgeElement Format")
    WriteEdgeElementFormat (mesh, filename);

  else if (format == "Chemnitz Format")
    WriteChemnitz (mesh, filename);

  else if (format == "Gmsh Format")
    WriteGmshFormat (mesh, filename);

  // Philippose - 29/01/2009
  // Added Gmsh v2.xx export capability
  else if (format == "Gmsh2 Format")
    WriteGmsh2Format (mesh, filename);

  else if (format == "VTU Format")
    WriteVTUFormat (mesh, filename, false, false);

  else if (format == "VTU Format, only volume")
    WriteVTUFormat (mesh, filename, true, false);

  else if (format == "DOLFIN Format")
    WriteDolfinFormat (mesh, filename);

  else if (format == "JCMwave Format")
    WriteJCMFormat (mesh, filename);

  else if (format == "TET Format")
    WriteTETFormat( mesh, filename);//, "High Frequency" );

  else
      return 1;

  return 0;
}




/*
 *  Neutral mesh format
 *  points, elements, surface elements
 */

void WriteNeutralFormat (const Mesh & mesh,
			 const string & filename)
{
  cout << "write neutral, new" << endl;
  int np = mesh.GetNP();
  int ne = mesh.GetNE();
  int nse = mesh.GetNSE();
  int nseg = mesh.GetNSeg();
  int i, j;

  int inverttets = mparam.inverttets;
  int invertsurf = mparam.inverttrigs;

  ofstream outfile (filename.c_str());

  outfile.precision(6);
  outfile.setf (ios::fixed, ios::floatfield);
  outfile.setf (ios::showpoint);

  outfile << np << "\n";

  for (i = 1; i <= np; i++)
    {
      const Point3d & p = mesh.Point(i);

      outfile.width(10);
      outfile << p.X() << " ";
      outfile.width(9);
      outfile << p.Y() << " ";
      if (mesh.GetDimension() == 3)
	{
	  outfile.width(9);
	  outfile << p.Z();
	  }
      outfile << "\n";
    }

  if (mesh.GetDimension() == 3)
    {
      outfile << ne << "\n";
      for (i = 1; i <= ne; i++)
	{
	  Element el = mesh.VolumeElement(i);
	  if (inverttets)
	    el.Invert();
	  outfile.width(4);
	  outfile << el.GetIndex() << "  ";
	  for (j = 1; j <= el.GetNP(); j++)
	    {
	      outfile << " ";
	      outfile.width(8);
	      outfile << el.PNum(j);
	    }
	  outfile << "\n";
	}
    }

  outfile << nse << "\n";
  for (i = 1; i <= nse; i++)
    {
      Element2d el = mesh.SurfaceElement(i);
      if (invertsurf)
	el.Invert();
      outfile.width(4);
      outfile << mesh.GetFaceDescriptor (el.GetIndex()).BCProperty() << "    ";
      for (j = 1; j <= el.GetNP(); j++)
	{
	  outfile << " ";
	  outfile.width(8);
	  outfile << el.PNum(j);
	}
      outfile << "\n";
    }


  if (mesh.GetDimension() == 2)
    {
      outfile << nseg << "\n";
      for (i = 1; i <= nseg; i++)
	{
	  const Segment & seg = mesh.LineSegment(i);
	  outfile.width(4);
	  outfile << seg.si << "    ";

	  outfile << " ";
	  outfile.width(8);
	  outfile << seg[0];
	  outfile << " ";
	  outfile.width(8);
	  outfile << seg[1];

	  outfile << "\n";
	}
    }
}


void WriteSurfaceFormat (const Mesh & mesh,
			 const string & filename)
{
  // surface mesh
  int i, j;

  cout << "Write Surface Mesh" << endl;

  ofstream outfile (filename.c_str());

  outfile << "surfacemesh" << endl;

  outfile << mesh.GetNP() << endl;
  for (i = 1; i <= mesh.GetNP(); i++)
    {
      for (j = 0; j < 3; j++)
	{
	  outfile.width(10);
	  outfile << mesh.Point(i)(j) << " ";
	}
      outfile << endl;
    }
  outfile << mesh.GetNSE() << endl;
  for (i = 1; i <= mesh.GetNSE(); i++)
    {
      for (j = 1; j <= 3; j++)
	{
	  outfile.width(8);
	  outfile << mesh.SurfaceElement(i).PNum(j);
	}
      outfile << endl;
    }
}


/*
 *  Edge element mesh format
 *  points, elements, edges
 */

void WriteEdgeElementFormat (const Mesh & mesh,
			     const string & filename)
{
  cout << "write edge element format" << endl;

  const MeshTopology * top = &mesh.GetTopology();
  int npoints = mesh.GetNP();
  int nelements = mesh.GetNE();
  int nsurfelem = mesh.GetNSE();
  int nedges = top->GetNEdges();
  int i, j;

  int inverttets = mparam.inverttets;
  int invertsurf = mparam.inverttrigs;
  Array<int> edges;

  ofstream outfile (filename.c_str());

  outfile.precision(6);
  outfile.setf (ios::fixed, ios::floatfield);
  outfile.setf (ios::showpoint);


  // vertices with coordinates
  outfile << npoints << "\n";
  for (i = 1; i <= npoints; i++)
    {
      const Point3d & p = mesh.Point(i);

      outfile.width(10);
      outfile << p.X() << " ";
      outfile.width(9);
      outfile << p.Y() << " ";
      outfile.width(9);
      outfile << p.Z() << "\n";
    }

  // element - edge - list
  outfile << nelements << " " << nedges << "\n";
  for (i = 1; i <= nelements; i++)
    {
      Element el = mesh.VolumeElement(i);
      if (inverttets)
      	el.Invert();
      outfile.width(4);
      outfile << el.GetIndex() << "  ";
      outfile.width(8);
      outfile << el.GetNP();
      for (j = 1; j <= el.GetNP(); j++)
	{
	  outfile << " ";
	  outfile.width(8);
	  outfile << el.PNum(j);
	}

      top->GetElementEdges(i,edges);
      outfile << endl << "      ";
      outfile.width(8);
      outfile << edges.Size();
      for (j=1; j <= edges.Size(); j++)
	{
	  outfile << " ";
	  outfile.width(8);
	  outfile << edges[j-1];
	}
      outfile << "\n";

      // orientation:
      top->GetElementEdgeOrientations(i,edges);
      outfile << "              ";
      for (j=1; j <= edges.Size(); j++)
	{
	  outfile << " ";
	  outfile.width(8);
	  outfile << edges[j-1];
	}
      outfile << "\n";
    }

  // surface element - edge - list (with boundary conditions)
  outfile << nsurfelem << "\n";
  for (i = 1; i <= nsurfelem; i++)
    {
      Element2d el = mesh.SurfaceElement(i);
      if (invertsurf)
	el.Invert();
      outfile.width(4);
      outfile << mesh.GetFaceDescriptor (el.GetIndex()).BCProperty() << "  ";
      outfile.width(8);
      outfile << el.GetNP();
      for (j = 1; j <= el.GetNP(); j++)
	{
	  outfile << " ";
	  outfile.width(8);
	  outfile << el.PNum(j);
	}

      top->GetSurfaceElementEdges(i,edges);
      outfile << endl << "      ";
      outfile.width(8);
      outfile << edges.Size();
      for (j=1; j <= edges.Size(); j++)
	{
	  outfile << " ";
	  outfile.width(8);
	  outfile << edges[j-1];
	}
      outfile << "\n";
    }


  int v1, v2;
  // edge - vertex - list
  outfile << nedges << "\n";
  for (i=1; i <= nedges; i++)
    {
      top->GetEdgeVertices(i,v1,v2);
      outfile.width(4);
      outfile << v1;
      outfile << " ";
      outfile.width(8);
      outfile << v2 << endl;
    }
}









#ifdef OLDSTYLE_WRITE


void WriteFile (int typ,
		const Mesh & mesh,
		const CSGeometry & geom,
		const char * filename,
		const char * geomfile,
		double h)
{


  int inverttets = mparam.inverttets;
  int invertsurf = mparam.inverttrigs;








  if (typ == WRITE_EDGEELEMENT)
    {
      // write edge element file
      // Peter Harscher, ETHZ

      cout << "Write Edge-Element Format" << endl;

      ofstream outfile (filename);

      int i, j;
      int ned;

      // hash table representing edges;
      INDEX_2_HASHTABLE<int> edgeht(mesh.GetNP());

      // list of edges
      Array<INDEX_2> edgelist;

      // edge (point) on boundary ?
      BitArray bedge, bpoint(mesh.GetNP());

      static int eledges[6][2] = { { 1, 2 } , { 1, 3 } , { 1, 4 },
				   { 2, 3 } , { 2, 4 } , { 3, 4 } };

      // fill hashtable   (point1, point2)  ---->  edgenr
      for (i = 1; i <= mesh.GetNE(); i++)
	{
	  const Element & el = mesh.VolumeElement (i);
	  INDEX_2 edge;
	  for (j = 1; j <= 6; j++)
	    {
	      edge.I1() = el.PNum (eledges[j-1][0]);
	      edge.I2() = el.PNum (eledges[j-1][1]);
	      edge.Sort();

	      if (!edgeht.Used (edge))
		{
		  edgelist.Append (edge);
		  edgeht.Set (edge, edgelist.Size());
		}
	    }
	}


      // set bedges, bpoints
      bedge.SetSize (edgelist.Size());
      bedge.Clear();
      bpoint.Clear();

      for (i = 1; i <= mesh.GetNSE(); i++)
	{
	  const Element2d & sel = mesh.SurfaceElement(i);
	  for (j = 1; j <= 3; j++)
	    {
	      bpoint.Set (sel.PNum(j));

	      INDEX_2 edge;
	      edge.I1() = sel.PNum(j);
	      edge.I2() = sel.PNum(j%3+1);
	      edge.Sort();

	      bedge.Set (edgeht.Get (edge));
	    }
	}



      outfile << mesh.GetNE() << endl;
      // write element ---> point
      for (i = 1; i <= mesh.GetNE(); i++)
	{
	  const Element & el = mesh.VolumeElement(i);

	  outfile.width(8);
	  outfile << i;
	  for (j = 1; j <= 4; j++)
	    {
	      outfile.width(8);
	      outfile << el.PNum(j);
	    }
	  outfile << endl;
	}

      // write element ---> edge
      for (i = 1; i <= mesh.GetNE(); i++)
	{
	  const Element & el = mesh.VolumeElement (i);
	  INDEX_2 edge;
	  for (j = 1; j <= 6; j++)
	    {
	      edge.I1() = el.PNum (eledges[j-1][0]);
	      edge.I2() = el.PNum (eledges[j-1][1]);
	      edge.Sort();

	      outfile.width(8);
	      outfile << edgeht.Get (edge);
	    }
	  outfile << endl;
	}

      // write points
      outfile << mesh.GetNP() << endl;
      outfile.precision (6);
      for (i = 1; i <= mesh.GetNP(); i++)
	{
	  const Point3d & p = mesh.Point(i);

	  for (j = 1; j <= 3; j++)
	    {
	      outfile.width(8);
	      outfile << p.X(j);
	    }
	  outfile << "       "
		  << (bpoint.Test(i) ? "1" : 0) << endl;
	}

      // write edges
      outfile << edgelist.Size() << endl;
      for (i = 1; i <= edgelist.Size(); i++)
	{
	  outfile.width(8);
	  outfile << edgelist.Get(i).I1();
	  outfile.width(8);
	  outfile << edgelist.Get(i).I2();
	  outfile << "       "
		  << (bedge.Test(i) ? "1" : "0") << endl;
	}
    }




}
#endif
}

