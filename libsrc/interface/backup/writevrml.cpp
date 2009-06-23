/*
 *  write surface mesh as VRML file
 */
// Bartosz Sawicki <sawickib@ee.pw.edu.pl>

#include "meshing.hpp"

namespace netgen
{

void WriteVRMLFormat (const Mesh & mesh,
        bool faces,
        const string & filename)
{
    int np = mesh.GetNP();
    int nse = mesh.GetNSE();
    int i, j;

    ofstream outfile (filename.c_str());
    outfile.precision(6);
    outfile.setf (ios::fixed, ios::floatfield);
    outfile.setf (ios::showpoint);

    if (faces)
    {
        // IndexedFaceSet is used
        outfile << "#VRML V2.0 utf8 \n"
            "Background {\n"
            "    skyColor [1 1 1]\n"
            "    groundColor [1 1 1]\n"
            "}\n"
            "Group{ children [\n"
            "Shape{ \n"
            "appearance Appearance { material Material { }} \n"
            "geometry IndexedFaceSet { \n"
            "coord Coordinate { point [ \n";
    }
    else
    {
        // IndexedLineSet is used
        outfile << "#VRML V2.0 utf8 \n"
            "Background {\n"
            "    skyColor [1 1 1]\n"
            "    groundColor [1 1 1]\n"
            "}\n"
            "Group{ children [\n"
            "Shape{ \n"
            "appearance Appearance { material Material { }} \n"
            "geometry IndexedLineSet { \n"
            "coord Coordinate { point [ \n";
    }

    for (i = 1; i <= np; i++)
    {
        const Point3d & p = mesh.Point(i);
        outfile.width(10);
        outfile << p.X() << " ";
        outfile << p.Y() << " ";
        outfile << p.Z() << " \n";
    }

    outfile << "  ] } \n"
        "coordIndex [ \n";

    for (i = 1; i <= nse; i++)
    {
        const Element2d & el = mesh.SurfaceElement(i);

        for (j = 1; j <= 3; j++)
        {
            outfile.width(8);
            outfile << el.PNum(j)-1;
        }
        if (faces) 
        {   
            outfile.width(8);
            outfile << el.PNum(1)-1;
        }
        outfile << " -1 \n";
    }

    outfile << "  ] \n";

    if (faces)
    {
        //define number and RGB definitions of colors
        outfile << "color Color { color [1 0 0, 0 1 0, 0 0 1, 1 1 0]} \n"
            "colorIndex [\n";

        for (i = 1; i <= nse; i++)
        {
            outfile << mesh.GetFaceDescriptor(mesh.SurfaceElement(i).GetIndex ()).BCProperty();
            outfile << endl;
        }

        outfile << " ] \n"
            "colorPerVertex FALSE \n"
            "creaseAngle 0 \n"
            "solid FALSE \n"
            "ccw FALSE \n"
            "convex TRUE \n"
            "} } # end of Shape\n"
            "] }\n";
    }
    else
    {
        outfile << "colorPerVertex FALSE \n"
            "} } #end of Shape\n"
            "] } \n";
    }

}

}
