#include <stdio.h>
#include <string>
#include <algorithm>

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
  std::string filename(argv[1]);
  std::string::size_type idx = filename.rfind('.');
  if(idx == std::string::npos) {
    printf("Couldn't determine file extension for %s\n",filename.c_str());
    return -1;
  }

  std::string extension = filename.substr(idx+1);
  std::transform(extension.begin(), extension.end(), extension.begin(), ::tolower);

  if (extension.compare("dae")==0) {
    vcg::tri::io::InfoDAE info;
    if (vcg::tri::io::ImporterDAE<MyMesh>::Open(m,filename.c_str(),info)!=0)
    {
      printf("Error reading DAE mesh from file %s\n",filename.c_str());
      return -1;
    }
  } else {
    printf("Error: Unknown extension %s\n",extension.c_str());
    return -1;
  }
  std::string objname = filename.substr(0,idx+1)+"obj";
  if (vcg::tri::io::ExporterOBJ<MyMesh>::Save(m,objname.c_str(),vcg::tri::io::ExporterOBJ<MyMesh>::GetExportMaskCapability()) != 0) {
    printf("Error writing %s\n",objname.c_str());
    return -1;
  }
  return 0;
}
