#ifndef FILE_INTERFACE
#define FILE_INTERFACE
/** \file interface.hpp
  * \brief Write and read functions for various file formats.
  * \author Many
  * \date 17 June 2009
  */

namespace netgen
{

/** Reads a mesh of native format.
  * \param[in,out] mesh Mesh to be filled.
  * \param[in] filename Path to file.
  * \ingroup interface
  */
void ReadFile (Mesh & mesh,
               const string & filename);

/** Reads a mesh of TET format.
  * \param[in,out] mesh Mesh to be filled.
  * \param[in] filename Path to file.
  * \ingroup interface
  */
void ReadTETFormat (Mesh & mesh,
                    const string & filename);

/** Reads a mesh of Pro/ENGINEER neutral format.
  * \param[in,out] mesh Mesh to be filled.
  * \param[in] filename Path to file.
  * \ingroup interface
  */
void ReadFNFFormat (Mesh & mesh,
                    const string & filename);

/** Gets the list of supported formats for writing.
  * \param[in,out] names Array with the names of the supported formats.
  */
void RegisterUserFormats (Array<const char*> & names);

/** Writes to the mesh to a file.
  * \param[in] format Format of output. 
  * \param[in] mesh  Mesh to be written.
  * \param[in] geom Geometry to be written (optional).
  * \param[in] filename Path to file.
  * \returns 1 when format was recognized otherwise 0
  * \ingroup interface
  */
bool WriteUserFormat (const string & format,
                      const Mesh & mesh,
                      const CSGeometry & geom,
                      const string & filename);

/* Deprecated.
void WriteFile (int type,
		const Mesh & mesh,
		const CSGeometry & geom,
		const char * filename,
		const char * geomfile = NULL,
		double h = 0);
*/

/** Writes mesh to netgens format.
  * Surface and volume mesh.
  * \param[in] mesh  Mesh to be written.
  * \param[in] filename Path to file.
  * \ingroup interface
  */
void WriteNeutralFormat (const Mesh & mesh,
                         const string & filename);

/** Writes mesh to netgens surface format.
  * Surface mesh only.
  * \param[in] mesh  Mesh to be written.
  * \param[in] filename Path to file.
  * \ingroup interface
  */
void WriteSurfaceFormat (const Mesh & mesh,
                         const string & filename);

/** Writes mesh to EdgeElement format.
  * Edges only.
  * \param[in] mesh  Mesh to be written.
  * \param[in] filename Path to file.
  * \ingroup interface
  */
void WriteEdgeElementFormat (const Mesh & mesh,
                             const string & filename);

/** Writes mesh to STL format.
  * Surface mesh, only triangles.
  * \param[in] mesh Mesh to be written.
  * \param[in] filename Path to file.
  * \ingroup interface
  */
void WriteSTLFormat (const Mesh & mesh,
                     const string & filename);

/** Writes mesh to VRML format.
  * Surface mesh only.
  * \author Bartosz Sawicki <sawickib@ee.edu.pl>
  * \param[in] mesh Mesh to be written.
  * \param[in] faces true to draw faces, otherwise only lines.
  * \param[in] filename Path to file.
  * \ingroup interface
  */
void WriteVRMLFormat (const Mesh & mesh,
                      bool faces,
                      const string & filename);

/** Writes mesh to FEPP format.
  * Volume mesh and CSG only.
  * \param[in] mesh Mesh to be written.
  * \param[in] geom Geometry to be written.
  * \param[in] filename Path to file.
  * \ingroup interface
  */
void WriteFEPPFormat (const Mesh & mesh,
                      const CSGeometry & geom,
                      const string & filename);

/** Writes mesh to Gmsh 1 format.
  * Only linear tetrahedra, triangles and quadrangles.
  * \author Paul Carrico
  * \param[in] mesh Mesh to be written.
  * \param[in] filename Path to file.
  * \ingroup interface
  */
void WriteGmshFormat (const Mesh & mesh,
                      const string & filename);

/** Writes mesh to Gmsh 2 format.
  * Current features of this function include:
  * 1. Exports Triangles, Quadrangles and Tetrahedra
  * 2. Supports upto second order elements of each type
  * \author Philippose Rajan
  * \param[in] mesh Mesh to be written.
  * \param[in] filename Path to file.
  * \ingroup interface
  */
void WriteGmsh2Format (const Mesh & mesh,
			           const string & filename);

/** Writes mesh to Chemnitz format.
  * Volume and surface.
  * \param[in] mesh Mesh to be written.
  * \param[in] filename Path to file.
  * \ingroup interface
  */
void WriteChemnitz (const Mesh & mesh,
                    const string & filename);

/** Writes mesh to JCMwave format.
  * Only Prisms and tetrahedrons, triangles and quadrangles.
  * \author Sven Burger
  * \param[in] mesh Mesh to be written.
  * \param[in] filename Path to file.
  * \ingroup interface
  */
void WriteJCMFormat (const Mesh & mesh,
                     const string & filename);

/** Writes mesh to DiffPack format.
  * Volume and surface.
  * \author Bartosz Sawicki <sawicki@ee.pw.edu.pl>
  * \author Jacques Lechelle <jacques.lechelle@wanadoo.fr>
  * \param[in] mesh Mesh to be written.
  * \param[in] filename Path to file.
  * \ingroup interface
  */
void WriteDiffPackFormat (const Mesh & mesh,
                          const string & filename);

/** Writes mesh to Tochnog format.
  * Only tetrahedrons.
  * \author Andreas Seltmann <a.Seltmann@lsw.uni-heidelberg.de>
  * \param[in] mesh Mesh to be written.
  * \param[in] filename Path to file.
  * \ingroup interface
  */
void WriteTochnogFormat (const Mesh & mesh,
                         const string & filename);

/** Writes mesh and geometry to TecPlot format.
  * Only tetrahedrons and triangles and CSG.
  * \author Jawor Georgview
  * \param[in] mesh Mesh to be written.
  * \param[in] geom Geometry to be written.
  * \param[in] filename Path to file.
  * \ingroup interface
  */
void WriteTecPlotFormat (const Mesh & mesh,
                         const CSGeometry & geom,
                         const string & filename);

/** Writes mesh to Abaqus format.
  * Only tetrahedrons (4 and 10 nodes).
  * Writes boundary conditions.
  * \param[in] mesh Mesh to be written.
  * \param[in] filename Path to file.
  * \ingroup interface
  */
void WriteAbaqusFormat (const Mesh & mesh,
                        const string & filename);

/** Writes mesh to Fluent format.
  * Only tetrahedrons. 
  * \author Johannes Gerstmayr
  * \param[in] mesh Mesh to be written.
  * \param[in] geom Geometry to be written.
  * \param[in] filename Path to file.
  * \ingroup interface
  */
void WriteFluentFormat (const Mesh & mesh,
                        const string & filename);

/** Writes mesh to Permas format.
  * Only tetrahedrons (4 or 10) and triangles (3 and 6) and quadrangles (4).
  * \param[in] mesh Mesh to be written.
  * \param[in] filename Path to file.
  * \ingroup interface
  */
void WritePermasFormat (const Mesh & mesh,
                        const string & filename);

/** Writes mesh to FEAP format.
  * Only volume.
  * \author Albrecht Rieger <rieger@ibnm.uni-hannover.do>
  * \param[in] mesh Mesh to be written.
  * \param[in] filename Path to file.
  * \ingroup interface
  */
void WriteFEAPFormat (const Mesh & mesh,
                      const string & filename);

/** Writes mesh to Elmer format..
  * Volume and surface.
  * \param[in] mesh Mesh to be written.
  * \param[in] filename Path to file.
  * \ingroup interface
  */
void WriteElmerFormat (const Mesh & mesh,
                       const string & filename);

/** Writes mesh to TET format.
  * Only tetrahedrons.
  * \param[in] mesh Mesh to be written.
  * \param[in] filename Path to file.
  * \ingroup interface
  */
void WriteTETFormat (const Mesh & mesh,
                     const string & filename);

/** Writes mesh to Dolfin format.
  * Only tetrahedrons.
  * \author Kent-Andre Mardal <kent-and@simula.no>
  * \param[in] mesh Mesh to be written.
  * \param[in] filename Path to file.
  * \ingroup interface
  */
void WriteDolfinFormat (const Mesh & mesh,
                        const string & filename);

/** Writes mesh to VTU format.
  * VTU is the VTK format for unstructured meshes. 
  * All elements in netgen is supported, no extra data.
  * \author Mikael Öhman <mikael.ohman@chalmers.se>
  * \param[in] mesh  Mesh to be written.
  * \param[in] filename Path to file.
  * \param[in] noSurf true to ignore surface elements.
  * \param[in] noVol true to ignore volume elements.
  * \ingroup interface
  */
bool WriteVTUFormat (const Mesh & mesh,
                     const string & filename,
                     bool noSurf = false,
                     bool noVol = false);

}
#endif
