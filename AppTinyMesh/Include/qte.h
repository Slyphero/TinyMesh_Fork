#ifndef __Qte__
#define __Qte__

#include "meshcolor.h"
#include "realtime.h"
#include <QtWidgets/qmainwindow.h>


QT_BEGIN_NAMESPACE
namespace Ui {
class Assets;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT
private:
  Ui::Assets *uiw; //!< Interface

  MeshWidget *meshWidget; //!< Viewer
  MeshColor meshColor;    //!< Mesh.

public:
  MainWindow();
  ~MainWindow();
  void CreateActions();
  void UpdateGeometry();

public slots:
  void editingSceneLeft(const Ray &);
  void editingSceneRight(const Ray &);
  void BoxMeshExample();
  void SphereImplicitExample();
  void BlobSphereExample();
  void TreeExample();
  void ResetCamera();
  void UpdateMaterial();
};

#endif
