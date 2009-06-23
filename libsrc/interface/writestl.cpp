/*
 *  save surface mesh as STL file
 */

#include "meshing.hpp"

namespace netgen
{

void WriteSTLFormat (const Mesh & mesh,
            const string & filename)
{
    cout << "\nWrite STL Surface Mesh" << endl;
    if (!mesh.PureTrigMesh())
    {
        cout << "Error: Mesh contains non trig element" << endl;
        return;
    }

    ofstream outfile (filename.c_str());
    outfile.precision(10);
    outfile << "solid" << endl;
    for (int i = 1; i <= mesh.GetNSE(); i++)
    {
        outfile << "facet normal ";
        const Point3d& p1 = mesh.Point(mesh.SurfaceElement(i).PNum(1));
        const Point3d& p2 = mesh.Point(mesh.SurfaceElement(i).PNum(2));
        const Point3d& p3 = mesh.Point(mesh.SurfaceElement(i).PNum(3));

        Vec3d normal = Cross(p2-p1,p3-p1);
        if (normal.Length() != 0)
            normal /= (normal.Length());

        outfile << normal.X() << " " << normal.Y() << " " << normal.Z() << "\n";
        outfile << "outer loop\n";

        outfile << "vertex " << p1.X() << " " << p1.Y() << " " << p1.Z() << "\n";
        outfile << "vertex " << p2.X() << " " << p2.Y() << " " << p2.Z() << "\n";
        outfile << "vertex " << p3.X() << " " << p3.Y() << " " << p3.Z() << "\n";

        outfile << "endloop\n";
        outfile << "endfacet\n";
    }
    outfile << "endsolid" << endl;
    outfile.close();
}

}
