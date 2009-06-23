/** \file writevtu.cpp
  * \author Mikael Öhman <mikael.ohman@chalmers.se>
  * \date 2009-06-17
  * \brief Write unstructured mesh (VTK format)
  * Handles all surface and volume elements except QUAD6 and PRISM12.
  * No segments (but it is possible and easy to add).
  * PointType, BCProperty, DomainIn, DomainOut, SurfNr are saved but no user data.
  */

#include "meshing.hpp"

namespace netgen
{

enum VTK_ELEMENTS {VTK_VERTEX=1,VTK_POLY_VERTEX,VTK_LINE,VTK_POLY_LINE,VTK_TRIANGLE,VTK_TRIANGLE_STRIP,
    VTK_POLYGON,VTK_PIXEL,VTK_QUAD,VTK_TETRA,VTK_VOXEL,VTK_HEXAHEDRON,VTK_WEDGE,VTK_PYRAMID,
    VTK_QUADRATIC_EDGE=21,VTK_QUADRATIC_TRIANGLE,VTK_QUADRATIC_QUAD,VTK_QUADRATIC_TETRA,VTK_QUADRATIC_HEXAHEDRON};

// Some reordering (netgen starts numbering from 0)
static int orderTri[6] = {1,2,3,6,4,5};
static int orderQuad[8] = {1,2,3,4,5,8,6,7};
static int orderTetra[10] = {1,3,2,4,6,8,5,7,10,9};
// These i dont know the order of, and i can't seem to generate any, but for now;
static int orderWedge[6] = {1,2,3,4,5,6};
static int orderPyramid[5] = {1,2,3,4,5};
static int orderHexahedron[8] = {1,2,3,4,5,6,7,8};

// Number of nodes per element. -1 for undefined elements and element strips 
// (those will intentionally cause errors in the vtu file, as they should never occur).
static int vtkOffset[26] = {
    0,1,-1,2,
    -1,3,-1,
    -1,4,4,
    4,8,8,
    6,5,
    -1,-1,-1,-1,-1,-1,
    3,6,8,
    10,20};

bool WriteVTUFormat (const Mesh & mesh, const string & filename, bool noSurf=false, bool noVol=false)
{
    cout << "Write VTU mesh" << endl;
    bool warnVolume = true;
    bool warnSurface = true;
    int np = mesh.GetNP();
    int ne = noVol ? 0 : mesh.GetNE();
    int nse = noSurf ? 0 : mesh.GetNSE();
    //int ns = noSeg ? 0 : mesh.GetNSeg();
    int *elType = NULL;
    int *sElType = NULL;
    if (ne > 0) elType = new int[ne];
    if (nse > 0) sElType = new int[nse];

    ofstream outfile(filename.c_str());
    outfile.precision(10);
    cout << "Writing points" << endl;
    outfile << "<?xml version=\"1.0\"?>\n";
    outfile << "<VTKFile type=\"UnstructuredGrid\" version=\"0.1\" byte_order=\"LittleEndian\">\n";
    outfile << "  <UnstructuredGrid>\n";
    outfile << "    <Piece NumberOfPoints=\"" << np << "\" NumberOfCells=\"" << (nse+ne) << "\">\n";
    outfile << "      <Points>\n";
    outfile << "        <DataArray type=\"Float32\" NumberOfComponents=\"3\" format=\"ascii\">\n";

    for (int i = 0; i < np; i++)
    {
        const Point3d& p = mesh.Point(i+1);
        outfile << p.X() << " " << p.Y() << " " << p.Z() << "\n";
    }
    outfile << "        </DataArray>\n";
    outfile << "      </Points>\n";
    cout << "Writing cells" << endl;
    outfile << "      <Cells>\n";
    outfile << "        <DataArray type=\"Int32\" Name=\"connectivity\" format=\"ascii\">\n";
    for (int i = 0; i < ne; i++) // write the volume elements, except for type (seperate node in the xml document)
    {
        int *order;
        elType[i] = 0;
        Element e = mesh.VolumeElement(i+1);
        if (mparam.inverttets) e.Invert();
        switch (e.GetType())
        {
            case TET:
                elType[i] = VTK_TETRA;
                order = orderTetra;
                break;
            case TET10:
                elType[i] = VTK_QUADRATIC_TETRA;
                order = orderTri;
                break;
            case PYRAMID:
                elType[i] = VTK_PYRAMID;
                order = orderPyramid;
                break;
            case PRISM:
                elType[i] = VTK_WEDGE;
                order = orderWedge;
                break;
            case HEX:
                elType[i] = VTK_HEXAHEDRON;
                order = orderHexahedron;
                break;
            default:
                if (warnVolume)
                {
                    cout << "Invalid element type " << e.GetType() << " for the VTU format." << endl;
                    warnVolume = false;
                    continue;
                }
        }
        for (int j = 0; j < e.GetNP(); j++)
            outfile << (e.PNum(order[j])-1) << " "; // subtract one since node number starts at 1 in netgen.
        outfile << "\n";
    }
    for (int i = 0; i < nse; i++) // and the same for the surface elements
    {
        int *order;
        sElType[i] = 0;
        Element2d e = mesh.SurfaceElement(i+1);
        if (mparam.inverttrigs) e.Invert();
        switch (e.GetType())
        {
            case TRIG:
                sElType[i] = VTK_TRIANGLE;
                order = orderTri;
                break;
            case TRIG6:
                sElType[i] = VTK_QUADRATIC_TRIANGLE;
                order = orderTri;
                break;
            case QUAD:
                sElType[i] = VTK_QUAD;
                order = orderQuad;
                break;
            case QUAD8:
                sElType[i] = VTK_QUADRATIC_QUAD;
                order = orderQuad;
                break;
            default:
                if (warnSurface)
                {
                    cout << "Invalid element type " << e.GetType() << " for the VTU format." << endl;
                    warnSurface = false;
                    continue;
                }
        }
        for (int j = 0; j < e.GetNP(); j++)
            outfile << (e.PNum(order[j])-1) << " ";
        outfile << "\n";
    }

    outfile << "        </DataArray>\n";
    outfile << "        <DataArray type=\"Int32\" Name=\"types\" format=\"ascii\">\n";
    for (int i = 0; i < ne; i++) outfile << elType[i] << " ";
    for (int i = 0; i < nse; i++) outfile << sElType[i] << " ";
    outfile << "\n";
    outfile << "        </DataArray>\n";
    outfile << "        <DataArray type=\"Int32\" Name=\"offsets\" format=\"ascii\">\n";
    int offset = 0;
    for (int i = 0; i < ne; i++) 
    {
        offset += vtkOffset[elType[i]];
        outfile << offset << " ";
    }
    for (int i = 0; i < nse; i++) 
    {
        offset += vtkOffset[sElType[i]];
        outfile << offset << " ";
    }
    outfile << "\n";
    outfile << "        </DataArray>\n";
    outfile << "      </Cells>\n";
    cout << "Writing cell data" << endl;
    outfile << "      <CellData>\n";
    /////////////////////// SurfNr ////////////////////////
    outfile << "        <DataArray type=\"Int32\" Name=\"SurfNr\" format=\"ascii\">\n";
    for (int i = 0; i < ne; i++) 
        outfile << mesh.GetFaceDescriptor(mesh.VolumeElement(i+1).GetIndex()).SurfNr() << " ";
    for (int i = 0; i < nse; i++) 
        outfile << mesh.GetFaceDescriptor(mesh.SurfaceElement(i+1).GetIndex()).SurfNr() << " ";
    outfile << "\n"; 
    outfile << "        </DataArray>\n";
    /////////////////////// BCProperty ////////////////////////
    outfile << "        <DataArray type=\"Int32\" Name=\"BCProperty\" format=\"ascii\">\n";
    for (int i = 0; i < ne; i++) 
        outfile << mesh.GetFaceDescriptor(mesh.VolumeElement(i+1).GetIndex()).BCProperty() << " ";
    for (int i = 0; i < nse; i++) 
        outfile << mesh.GetFaceDescriptor(mesh.SurfaceElement(i+1).GetIndex()).BCProperty() << " ";
    outfile << "\n"; 
    outfile << "        </DataArray>\n";
    /////////////////////// DomainIn ////////////////////////
    outfile << "        <DataArray type=\"Int32\" Name=\"DomainIn\" format=\"ascii\">\n";
    for (int i = 0; i < ne; i++) 
        outfile << mesh.GetFaceDescriptor(mesh.VolumeElement(i+1).GetIndex()).DomainIn() << " ";
    for (int i = 0; i < nse; i++) 
        outfile << mesh.GetFaceDescriptor(mesh.SurfaceElement(i+1).GetIndex()).DomainIn() << " ";
    outfile << "\n";
    outfile << "        </DataArray>\n";
    /////////////////////// DomainOut ////////////////////////
    outfile << "        <DataArray type=\"Int32\" Name=\"DomainOut\" format=\"ascii\">\n";
    for (int i = 0; i < ne; i++) 
        outfile << mesh.GetFaceDescriptor(mesh.VolumeElement(i+1).GetIndex()).DomainOut() << " ";
    for (int i = 0; i < nse; i++) 
        outfile << mesh.GetFaceDescriptor(mesh.SurfaceElement(i+1).GetIndex()).DomainOut() << " ";
    outfile << "\n"; 
    outfile << "        </DataArray>\n";
    outfile << "      </CellData>\n";
    cout << "Writing point data" << endl;
    outfile << "      <PointData>\n";
    outfile << "        <DataArray type=\"Int32\" Name=\"PointType\" format=\"ascii\">\n";
    for (int i = 0; i < np; i++)
        outfile << mesh.Point(i+1).Type() << " ";
    outfile << "\n";
    outfile << "        </DataArray>\n";
    outfile << "      </PointData>\n";
    outfile << "    </Piece>\n";
    outfile << "  </UnstructuredGrid>\n";
    outfile << "</VTKFile>";
    outfile.close();
    cout << "Done writing file." << endl;
    if (elType) delete(elType);
    if (sElType) delete(sElType);
    return true;
}

}
