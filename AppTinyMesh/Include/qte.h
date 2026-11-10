#ifndef __Qte__
#define __Qte__

#include <QtWidgets/qmainwindow.h>
#include <chrono>
#include <random>

#include "meshcolor.h"
#include "realtime.h"

QT_BEGIN_NAMESPACE
namespace Ui
{
class Assets;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
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

    void TreeExample();
    void BlobSphereExample();
    void BlobCapsuleExample();
    void ShowSDFExample();
    void ShowOperatorsExample();
    void ShowInfiniteBlobSphere();

    void Benchmark();
    void MeshQuality();

    void Tentacle();

    void ResetCamera();
    void UpdateMaterial();
};

#endif
