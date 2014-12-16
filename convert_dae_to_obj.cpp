#include <stdio.h>
#include <string>

#ifdef __APPLE__
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#else
#ifdef _WIN32
#include <windows.h>
#endif
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#endif

#include <vcg/complex/complex.h>
#include <wrap/io_trimesh/import.h>
#include <wrap/io_trimesh/import_dae.h>
#include <wrap/io_trimesh/export.h>

class MyVertex; class MyEdge; class MyFace;
struct MyUsedTypes : public vcg::UsedTypes<vcg::Use<MyVertex> ::AsVertexType,
vcg::Use<MyEdge> ::AsEdgeType,
vcg::Use<MyFace> ::AsFaceType>{};

class MyVertex : public vcg::Vertex< MyUsedTypes, vcg::vertex::Coord3f, vcg::vertex::Normal3f, vcg::vertex::BitFlags >{};
class MyFace : public vcg::Face< MyUsedTypes, vcg::face::FFAdj, vcg::face::VertexRef, vcg::face::BitFlags > {};
class MyEdge : public vcg::Edge< MyUsedTypes> {};
class MyMesh : public vcg::tri::TriMesh< std::vector<MyVertex>, std::vector<MyFace> , std::vector<MyEdge> > {};


int main(int argc, char* argv[])
{
  // definition of type MyMesh
  MyMesh m;
  vcg::tri::io::InfoDAE info;
  std::string filename(argv[1]);
  std::string daename = filename+".dae";
  if (vcg::tri::io::ImporterDAE<MyMesh>::Open(m,daename.c_str(),info)!=vcg::tri::io::ImporterOFF<MyMesh>::NoError)
  {
    printf("Error reading file %s\n",daename.c_str());
    exit(-1);
  }
  std::string objname = filename+".obj";
  vcg::tri::io::ExporterOBJ<MyMesh>::Save(m,objname.c_str(),vcg::tri::io::ExporterOBJ<MyMesh>::GetExportMaskCapability());
  return 0;
}
