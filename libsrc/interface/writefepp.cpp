/*
 * FEPP .. a finite element package developed at University Linz, Austria
 */

#include "csg.hpp"
#include "meshing.hpp"

namespace netgen
{

void WriteFEPPFormat (const Mesh & mesh,
		      const CSGeometry & geom,
		      const string & filename)
{

  ofstream outfile (filename.c_str());

  if (mesh.GetDimension() == 3)

    {

      // output for FEPP

      int np = mesh.GetNP();
      int ne = mesh.GetNE();
      int nse = mesh.GetNSE();
      int ns = mesh.GetNFD();
      int i, j;

      outfile.precision(5);
      outfile.setf (ios::fixed, ios::floatfield);
      outfile.setf (ios::showpoint);

      outfile << "volumemesh4" << endl;
      outfile << nse << endl;
      for (i = 1; i <= nse; i++)
	{
	  const Element2d & el = mesh.SurfaceElement(i);

	  //	  int facenr = mesh.facedecoding.Get(el.GetIndex()).surfnr;
	  outfile.width(4);
	  outfile << el.GetIndex() << " ";
	  outfile.width(4);
	  //	  outfile << mesh.GetFaceDescriptor(el.GetIndex()).BCProperty() << " ";
	  outfile << mesh.GetFaceDescriptor(el.GetIndex()).BCProperty() << " ";
	  outfile.width(4);
	  outfile << el.GetNP() << "    ";
	  for (j = 1; j <= el.GetNP(); j++)
	    {
	      outfile.width(8);
	      outfile << el.PNum(j);
	    }
	  outfile << "\n";
	}


      outfile << ne << "\n";
      for (i = 1; i <= ne; i++)
	{
	  const Element & el = mesh.VolumeElement(i);
	  outfile.width(4);
	  outfile << el.GetIndex() << " ";
	  outfile.width(4);
	  outfile << el.GetNP() << " ";
	  for (j = 1; j <= el.GetNP(); j++)
	    {
	      outfile.width(8);
	      outfile << el.PNum(j);
	    }
	  outfile << "\n";
	}

      outfile << np << "\n";
      for (i = 1; i <= np; i++)
	{
	  const Point3d & p = mesh.Point(i);

	  outfile.width(10);
	  outfile << p.X() << " ";
	  outfile.width(9);
	  outfile << p.Y() << " ";
	  outfile.width(9);
	  outfile << p.Z() << "\n";
	}

      /*
      if (typ == WRITE_FEPPML)
	{
	  int nbn =  mesh.mlbetweennodes.Size();
	  outfile << nbn << "\n";
	  for (i = 1; i <= nbn; i++)
	    outfile << mesh.mlbetweennodes.Get(i).I1() << " "
		    << mesh.mlbetweennodes.Get(i).I2() << "\n";


	  //	  int ncon = mesh.connectedtonode.Size();
	  //	  outfile << ncon << "\n";
	  //	  for (i = 1; i <= ncon; i++)
	  //	    outfile << i << " " << mesh.connectedtonode.Get(i) << endl;
	}
      */


      // write CSG surfaces
      if (&geom && geom.GetNSurf() >= ns)
	{
	  outfile << ns << endl;
	  for (i = 1; i <= ns; i++)
	    geom.GetSurface(mesh.GetFaceDescriptor(i).SurfNr())->Print(outfile);
	}
      else
	outfile << "0" << endl;
    }


  else

    { // 2D fepp format

      ;
      /*
      extern SplineGeometry2d * geometry2d;
      if (geometry2d)
	Save2DMesh (mesh, &geometry2d->GetSplines(), outfile);
      else
	Save2DMesh (mesh, 0, outfile);
      */
    }
}

}
