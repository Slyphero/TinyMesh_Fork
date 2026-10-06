#include "qte.h"
#include "implicits.h"
#include "ui_interface.h"

MainWindow::MainWindow() : QMainWindow(), uiw(new Ui::Assets)
{
	// Chargement de l'interface
    uiw->setupUi(this);

	// Chargement du GLWidget
	meshWidget = new MeshWidget;
	QGridLayout* GLlayout = new QGridLayout;
	GLlayout->addWidget(meshWidget, 0, 0);
	GLlayout->setContentsMargins(0, 0, 0, 0);
    uiw->widget_GL->setLayout(GLlayout);

	// Creation des connect
	CreateActions();

	meshWidget->SetCamera(Camera(Vector(10, 0, 0), Vector(0.0, 0.0, 0.0)));
}

MainWindow::~MainWindow()
{
	delete meshWidget;
}

void MainWindow::CreateActions()
{
	// Buttons
    connect(uiw->boxMesh, SIGNAL(clicked()), this, SLOT(BoxMeshExample()));
    connect(uiw->sphereImplicit, SIGNAL(clicked()), this, SLOT(SphereImplicitExample()));
    connect(uiw->blob, SIGNAL(clicked()), this, SLOT(BlobSphereExample()));
    connect(uiw->tree, SIGNAL(clicked()), this, SLOT(TreeExample()));
    connect(uiw->resetcameraButton, SIGNAL(clicked()), this, SLOT(ResetCamera()));
    connect(uiw->wireframe, SIGNAL(clicked()), this, SLOT(UpdateMaterial()));
    connect(uiw->radioShadingButton_1, SIGNAL(clicked()), this, SLOT(UpdateMaterial()));
    connect(uiw->radioShadingButton_2, SIGNAL(clicked()), this, SLOT(UpdateMaterial()));

	// Widget edition
	connect(meshWidget, SIGNAL(_signalEditSceneLeft(const Ray&)), this, SLOT(editingSceneLeft(const Ray&)));
	connect(meshWidget, SIGNAL(_signalEditSceneRight(const Ray&)), this, SLOT(editingSceneRight(const Ray&)));
}

void MainWindow::editingSceneLeft(const Ray&)
{
}

void MainWindow::editingSceneRight(const Ray&)
{
}

void MainWindow::BoxMeshExample()
{
    Mesh boxMesh = Mesh(Box(1.0));

	std::vector<Color> cols;
    cols.resize(boxMesh.Vertexes());
    for (size_t i = 0; i < cols.size(); i++)
		cols[i] = Color(double(i) / 6.0, fmod(double(i) * 39.478378, 1.0), 0.0);

	meshColor = MeshColor(boxMesh, cols, boxMesh.VertexIndexes());
	UpdateGeometry();
}

void MainWindow::SphereImplicitExample()
{
  AnalyticScalarField implicit;

  Mesh implicitMesh;
  implicit.Polygonize(31, implicitMesh, Box(2.0));

  std::vector<Color> cols;
  cols.resize(implicitMesh.Vertexes());
  for (size_t i = 0; i < cols.size(); i++)
    cols[i] = Color(0.8, 0.8, 0.8);

  meshColor = MeshColor(implicitMesh, cols, implicitMesh.VertexIndexes());
  UpdateGeometry();
}

void MainWindow::BlobSphereExample()
{
    AnalyticBlob implicit;

    for (int i = 0; i < 4; i++)
        implicit.AddBlob(std::make_shared<BlobSphere>(1.0, Vector(1.0 * i, 0.0, 0.0)));

    Mesh implicitMesh;
    implicit.Polygonize(31, implicitMesh, Box(4.0));

    std::vector<Color> cols;
    cols.resize(implicitMesh.Vertexes());
    for (size_t i = 0; i < cols.size(); ++i)
        cols[i] = Color(0.2, 0.6, 0.9);

    meshColor = MeshColor(implicitMesh, cols, implicitMesh.VertexIndexes());
    UpdateGeometry();
}

void MainWindow::TreeExample()
{
    AnalyticTree tree;
    Mesh implicitMesh;

    std::shared_ptr<ImplicitBlob> blob1 = std::make_shared<ImplicitBlob>();
    std::shared_ptr<ImplicitBlob> blob2 = std::make_shared<ImplicitBlob>();

    for (int i = 0; i < 4; i++)
        blob1->AddPotential(std::make_shared<PotentialSphere>(1.0, Vector(1.0 * i, 0.0, 0.0)));

    for (int i = 0; i < 5; i++)
        blob2->AddPotential(std::make_shared<PotentialSphere>(1.0, Vector(1.0 * i, 3.0, 0.0)));

    std::shared_ptr<ImplicitNode> root = std::make_shared<ImplicitUnion>(blob1, blob2);

    tree.SetRoot(root);

    tree.Polygonize(31, implicitMesh, Box(10.0));

    std::vector<Color> cols;
    cols.resize(implicitMesh.Vertexes());
    for (size_t i = 0; i < cols.size(); i++)
    {
        cols[i] = Color(0.2, 0.6, 0.9);
    }

    meshColor = MeshColor(implicitMesh, cols, implicitMesh.VertexIndexes());
    UpdateGeometry();
}

void MainWindow::UpdateGeometry()
{
	meshWidget->ClearAll();
	meshWidget->AddMesh("BoxMesh", meshColor);

    uiw->lineEdit->setText(QString::number(meshColor.Vertexes()));
    uiw->lineEdit_2->setText(QString::number(meshColor.Triangles()));

	UpdateMaterial();
}

void MainWindow::UpdateMaterial()
{
    meshWidget->UseWireframeGlobal(uiw->wireframe->isChecked());

    if (uiw->radioShadingButton_1->isChecked())
		meshWidget->SetMaterialGlobal(MeshMaterial::Normal);
	else
		meshWidget->SetMaterialGlobal(MeshMaterial::Color);
}

void MainWindow::ResetCamera()
{
	meshWidget->SetCamera(Camera(Vector(-10.0), Vector(0.0)));
}
