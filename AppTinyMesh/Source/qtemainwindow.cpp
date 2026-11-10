

#include "implicits.h"
#include "qte.h"
#include "ui_interface.h"
#include "macros.h"

MainWindow::MainWindow() : QMainWindow(), uiw(new Ui::Assets)
{
    // Chargement de l'interface
    uiw->setupUi(this);

    // Chargement du GLWidget
    meshWidget = new MeshWidget;
    QGridLayout *GLlayout = new QGridLayout;
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
    CREATE_SCENE(boxMesh, BoxMeshExample);
    CREATE_SCENE(sphereImplicit, SphereImplictExample);

    CREATE_SCENE(tree, TreeExample);
    CREATE_SCENE(blobSphere, BlobSphereExample);
    CREATE_SCENE(blobCapsule, BlobCapsuleExample);
    CREATE_SCENE(showSDF, ShowSDFExample);
    CREATE_SCENE(showOperators, ShowOperatorsExample);

    CREATE_SCENE(benchmark, Benchmark);
    CREATE_SCENE(meshQuality, MeshQuality);

    CREATE_SCENE(resetcameraButton, ResetCamera);
    CREATE_SCENE(wireframe, UpdateMaterial);
    CREATE_SCENE(radioShadingButton_1, UpdateMaterial);
    CREATE_SCENE(radioShadingButton_2, UpdateMaterial);

    // Widget edition
    connect(meshWidget, SIGNAL(_signalEditSceneLeft(const Ray &)), this,
            SLOT(editingSceneLeft(const Ray &)));
    connect(meshWidget, SIGNAL(_signalEditSceneRight(const Ray &)), this,
            SLOT(editingSceneRight(const Ray &)));
}

void MainWindow::editingSceneLeft(const Ray &)
{
}

void MainWindow::editingSceneRight(const Ray &)
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

void MainWindow::TreeExample()
{
    AnalyticTree tree;
    Mesh implicitMesh;

    std::shared_ptr<ImplicitBlob> blob1 = std::make_shared<ImplicitBlob>(0.5);
    std::shared_ptr<ImplicitBlob> blob2 = std::make_shared<ImplicitBlob>(0.7);

    for (int i = 0; i < 4; i++)
    {
        blob1->AddPotential(std::make_shared<PotentialSphere>(1.0, Vector(1.2 * i, 0.0, 0.0)));
    }
    for (int i = 0; i < 5; i++)
    {
        blob2->AddPotential(std::make_shared<PotentialCapsule>(1.0, Vector(1.0, 3.0 + 1.2 * i, 0.0),
                                                               Vector(2.0, 3.0 + 1.2 * i, 0.0)));
    }

    std::shared_ptr<ImplicitNode> blobs = std::make_shared<ImplicitUnion>(blob1, blob2);
    std::shared_ptr<ImplicitNode> sdfSphere =
        std::make_shared<SDFSphere>(1.0, Vector(1.0, 0.0, 0.0));

    std::shared_ptr<ImplicitNode> difference =
        std::make_shared<ImplicitDifference>(blobs, sdfSphere);

    std::shared_ptr<ImplicitNode> sdfCapsule =
        std::make_shared<SDFCapsule>(1.0, Vector(1.0, 0.0, 2.0), Vector(2.0, 0.0, 2.0));

    std::shared_ptr<ImplicitNode> union1 = std::make_shared<ImplicitUnion>(difference, sdfCapsule);

    std::shared_ptr<ImplicitNode> torus =
        std::make_shared<SDFTorus>(2.0, 0.75, Vector(1.0, 1.0, 1.0));

    std::shared_ptr<ImplicitNode> union2 = std::make_shared<ImplicitUnion>(union1, torus);

    std::shared_ptr<ImplicitNode> sdfBox =
        std::make_shared<SDFBox>(1.0, 2.0, 1.0, Vector(2.0, 2.0, 2.0));

    std::shared_ptr<ImplicitNode> union3 = std::make_shared<ImplicitUnion>(union2, sdfBox);

    std::shared_ptr<ImplicitNode> sdfSphere2 =
        std::make_shared<SDFSphere>(1., Vector(4.5, 3.5, 3.0));

    std::shared_ptr<ImplicitNode> union4 =
        std::make_shared<ImplicitSmoothUnion>(union3, sdfSphere2, 1.50);

    std::shared_ptr<ImplicitNode> root = std::make_shared<ImplicitScale>(union4, 0.75);
    tree.SetRoot(root);

    tree.Polygonize(150, implicitMesh, Box(10.0));

    std::vector<Color> cols;
    cols.resize(implicitMesh.Vertexes());
    for (size_t i = 0; i < cols.size(); i++)
    {
        cols[i] = Color(0.2, 0.6, 0.9);
    }

    meshColor = MeshColor(implicitMesh, cols, implicitMesh.VertexIndexes());
    UpdateGeometry();
}

void MainWindow::BlobSphereExample()
{
    AnalyticTree tree;
    Mesh implicitMesh;

    std::shared_ptr<ImplicitBlob> blob = std::make_shared<ImplicitBlob>(0.5);

    std::shared_ptr<PotentialSphere> pot1 =
        std::make_shared<PotentialSphere>(1.0, Vector(0.0, 0.0, 0.0));
    pot1->SetColor(Color(1.0, 0.0, 0.0));
    blob->AddPotential(pot1);

    std::shared_ptr<PotentialSphere> pot2 =
        std::make_shared<PotentialSphere>(1.5, Vector(0.0, 1.5, 0.0));
    pot2->SetColor(Color(0.0, 1.0, 0.0));
    blob->AddPotential(pot2);

    std::shared_ptr<PotentialSphere> pot3 =
        std::make_shared<PotentialSphere>(0.5, Vector(1.2, 1.2, 0.0));
    pot3->SetColor(Color(0.0, 0.0, 1.0));
    blob->AddPotential(pot3);

    std::shared_ptr<PotentialSphere> pot4 =
        std::make_shared<PotentialSphere>(2., Vector(1.5, 0.0, 1.0));
    pot4->SetColor(Color(1.0, 0.0, 1.0));
    blob->AddPotential(pot4);

    std::shared_ptr<ImplicitNode> root = blob;
    tree.SetRoot(root);

    tree.Polygonize(150, implicitMesh, Box(10.0));

    std::vector<Color> cols;
    cols.resize(implicitMesh.Vertexes());

    for (size_t i = 0; i < cols.size(); i++)
    {
        cols[i] = root->ColorAt(implicitMesh.Vertex(i));
    }

    meshColor = MeshColor(implicitMesh, cols, implicitMesh.VertexIndexes());

    UpdateGeometry();
}

void MainWindow::BlobCapsuleExample()
{
    AnalyticTree tree;
    Mesh implicitMesh;
    std::shared_ptr<ImplicitBlob> blob = std::make_shared<ImplicitBlob>(0.7);

    std::shared_ptr<PotentialCapsule> pot1 =
        std::make_shared<PotentialCapsule>(1.0, Vector(0.0, 0.0, 0.0), Vector(1.5, 0.5, 0.0));
    pot1->SetColor(Color(1.0, 0.0, 0.0));
    blob->AddPotential(pot1);

    std::shared_ptr<PotentialCapsule> pot2 =
        std::make_shared<PotentialCapsule>(1.0, Vector(2.5, 0.7, 0.0), Vector(3.0, 0.7, 0));
    pot2->SetColor(Color(0.0, 0.0, 1.0));
    blob->AddPotential(pot2);

    std::shared_ptr<PotentialCapsule> pot3 =
        std::make_shared<PotentialCapsule>(1.0, Vector(1.5, 1.7, 0.0), Vector(3.5, 1.9, 0.));
    pot3->SetColor(Color(0.0, 1.0, 0.0));
    blob->AddPotential(pot3);

    std::shared_ptr<ImplicitNode> root = blob;
    tree.SetRoot(root);
    tree.Polygonize(150, implicitMesh, Box(10.0));

    std::vector<Color> cols;
    cols.resize(implicitMesh.Vertexes());

    for (size_t i = 0; i < cols.size(); i++)
    {
        cols[i] = root->ColorAt(implicitMesh.Vertex(i));
    }

    meshColor = MeshColor(implicitMesh, cols, implicitMesh.VertexIndexes());

    UpdateGeometry();
}

void MainWindow::ShowSDFExample()
{
    AnalyticTree tree;
    Mesh implicitMesh;

    std::shared_ptr<SDFSphere> sphere = std::make_shared<SDFSphere>(1, Vector(-2, 0, 0));
    sphere->SetColor(Color(1.0, 1.0, 0.0));

    std::shared_ptr<SDFCapsule> capsule =
        std::make_shared<SDFCapsule>(1, Vector(.5, 0, 0), Vector(.5, 0, 1));
    capsule->SetColor(Color(1.0, 0.0, 0.0));

    std::shared_ptr<SDFTorus> torus = std::make_shared<SDFTorus>(1, .5, Vector(3.5, 0, 0));
    torus->SetColor(Color(0.0, 1.0, 0.0));

    std::shared_ptr<SDFBox> box = std::make_shared<SDFBox>(1, 1.5, 1.5, Vector(-4.5, 0, 0));
    box->SetColor(Color(0.0, 0.0, 1.0));

    std::shared_ptr<SDFEllipsoid> ellipsoid = std::make_shared<SDFEllipsoid>(2, 1, 1, Vector(0, 0, -2.5));
    ellipsoid->SetColor(Color(1.0, 0.0, 1.0));

    std::shared_ptr<ImplicitUnion> union1 = std::make_shared<ImplicitUnion>(sphere, capsule);
    std::shared_ptr<ImplicitUnion> union2 = std::make_shared<ImplicitUnion>(union1, torus);
    std::shared_ptr<ImplicitUnion> union3 = std::make_shared<ImplicitUnion>(union2, box);
    std::shared_ptr<ImplicitUnion> union4 = std::make_shared<ImplicitUnion>(union3, ellipsoid);

    std::shared_ptr<ImplicitNode> root = union4;
    tree.SetRoot(root);
    tree.Polygonize(150, implicitMesh, Box(10.0));

    std::vector<Color> cols;
    cols.resize(implicitMesh.Vertexes());

    for (size_t i = 0; i < cols.size(); i++)
    {
        cols[i] = root->ColorAt(implicitMesh.Vertex(i));
    }

    meshColor = MeshColor(implicitMesh, cols, implicitMesh.VertexIndexes());

    UpdateGeometry();
}

void MainWindow::ShowOperatorsExample()
{
    AnalyticTree tree;
    Mesh implicitMesh;

    std::shared_ptr<SDFSphere> sphere = std::make_shared<SDFSphere>(1, Vector(-2, 0, 0));
    sphere->SetColor(Color(1.0, 0.0, 0.0));

    std::shared_ptr<SDFBox> box = std::make_shared<SDFBox>(1, 1.5, 1.5, Vector(0, 0, 0));
    box->SetColor(Color(0.0, 1.0, 0.0));

    std::shared_ptr<SDFCapsule> capsule =
        std::make_shared<SDFCapsule>(1, Vector(0, -1, 0), Vector(0, -1, 1.5));
    capsule->SetColor(Color(0, 0, 1));

    std::shared_ptr<SDFTorus> torus = std::make_shared<SDFTorus>(1, .5, Vector(0, 0, -2.5));
    torus->SetColor(Color(1.0, 1.0, 0.0));

    std::shared_ptr<SDFTorus> torus2 = std::make_shared<SDFTorus>(1, .5, Vector(2, 0, -2.5));
    torus2->SetColor(Color(1.0, 0.0, 1.0));

    std::shared_ptr<ImplicitNode> union1 = std::make_shared<ImplicitSmoothUnion>(sphere, box, 1.50);
    std::shared_ptr<ImplicitNode> difference = std::make_shared<ImplicitDifference>(union1, capsule);
    std::shared_ptr<ImplicitNode> intersect1 = std::make_shared<ImplicitIntersection>(torus, torus2);
    std::shared_ptr<ImplicitNode> union2 = std::make_shared<ImplicitUnion>(difference, intersect1);

    std::shared_ptr<ImplicitNode> root = union2;
    tree.SetRoot(root);
    tree.Polygonize(150, implicitMesh, Box(10.0));

    std::vector<Color> cols;
    cols.resize(implicitMesh.Vertexes());

    for (size_t i = 0; i < cols.size(); i++)
    {
        cols[i] = root->ColorAt(implicitMesh.Vertex(i));
    }

    meshColor = MeshColor(implicitMesh, cols, implicitMesh.VertexIndexes());
    UpdateGeometry();
}

static volatile double g_sink = 0.0;

static double BenchmarkNode(const ImplicitNode &node,
                            const std::vector<Vector> &points,
                            size_t count,
                            int repeats = 5)
{
    const size_t mask = points.size() - 1;
    double best = 1e30;

    for (int r = 0; r < repeats; r++)
    {
        double sink = 0.0;
        auto start = std::chrono::steady_clock::now();

        for (size_t i = 0; i < count; i++)
        {
            sink += node.Value(points[i & mask]);
        }

        auto end = std::chrono::steady_clock::now();
        g_sink = sink;

        double ms = std::chrono::duration<double, std::milli>(end - start).count();
        if (ms < best)
        {
            best = ms;
        }
    }

    return best;
}

void MainWindow::Benchmark()
{
    std::mt19937 gen(42);
    std::uniform_real_distribution<double> dist(-5.0, 5.0);
    std::vector<Vector> points(1 << 16);

    for (Vector &p : points)
    {
        p = Vector(dist(gen), dist(gen), dist(gen));
    }

    const size_t count = 1e8;

    std::vector< std::pair<std::string, std::shared_ptr<ImplicitNode>> > nodes;

    auto sphere = std::make_shared<SDFSphere>(1.0, Vector(0, 0, 0));
    auto capsule = std::make_shared<SDFCapsule>(1.0, Vector(-1, 0, 0), Vector(1, 0, 0));
    auto torus = std::make_shared<SDFTorus>(2.0, 0.5, Vector(0, 0, 0));
    auto box = std::make_shared<SDFBox>(1.0, 2.0, 1.0, Vector(0, 0, 0));
    auto ellipsoid = std::make_shared<SDFEllipsoid>(1.0, 2.0, 1.0, Vector(0.0, 0.0, 0.0));

    nodes.push_back({"Sphere", sphere});
    nodes.push_back({"Capsule", capsule});
    nodes.push_back({"Torus", torus});
    nodes.push_back({"Box", box});
    nodes.push_back({"Ellipsoid", ellipsoid});
    nodes.push_back({"Union(sphere, box)", std::make_shared<ImplicitUnion>(sphere, box)});
    nodes.push_back({"SmoothUnion(sphere, box)",
                    std::make_shared<ImplicitSmoothUnion>(sphere, box, 0.5)});

    auto blob = std::make_shared<ImplicitBlob>(0.5);

    for (int i = 0; i < 10; i++)
    {
        blob->AddPotential(std::make_shared<PotentialSphere>(1.0, Vector(i * 0.5 - 2.5, 0, 0)));
    }

    nodes.push_back({"Blob (10 potentiels)", blob});

    std::cout << "Benchmark " << count << " evaluations de Value \n";
    for (const auto& [name, node] : nodes)
    {
        BenchmarkNode(*node, points, count / 10, 1);
        double ms = BenchmarkNode(*node, points, count);
        std::cout << name << " : " << ms << " ms ("
                  << (ms * 1e6 / count)  << " ns/appel)" << std::endl;
    }
}

static double TriangleAspect(const Vector &a, const Vector &b, const Vector &c)
{
    double la = Norm(b - c);
    double lb = Norm(a - c);
    double lc = Norm(a - b);

    double abc = la * lb * lc;

    if (abc < 1e-18)
    {
        return 0.0;
    }

    double s = (la + lb + lc) / 2.0;
    double u = (s - la) * (s - lb) * (s - lc);

    if (u < 0.0)
    {
        u = 0.0;
    }

    return 8 * u / abc;
}

struct MeshStats
{
    size_t vertices = 0;
    size_t triangles = 0;

    double rhoMean = 0;
    double rhoMin = 1;
    double badRatio = 0; // Part des triangles avec rho < 0.3

    double errorMean = 0;
    double errorMax = 0;
};

static MeshStats ComputeStats(const Mesh &mesh, const ImplicitNode &node)
{
    MeshStats s;
    s.vertices = mesh.Vertexes();
    s.triangles = mesh.Triangles();

    const std::vector<int> &idx = mesh.VertexIndexes();

    size_t bad = 0;
    for (size_t i = 0; i + 2 < idx.size(); i += 3)
    {
        const Vector &a = mesh.Vertex(idx[i]);
        const Vector &b = mesh.Vertex(idx[i + 1]);
        const Vector &c = mesh.Vertex(idx[i + 2]);

        double rho = TriangleAspect(a, b, c);
        s.rhoMean += rho;
        s.rhoMin = Math::Min(rho, s.rhoMin);

        Vector g = (a + b + c) / 3.0;
        double e = std::abs(node.Value(g));
        s.errorMean += e;
        s.errorMax = Math::Max(s.errorMax, e);

        if (rho < 0.3)
        {
            bad++;
        }
    }

    s.rhoMean /= s.triangles;
    s.errorMean /= s.triangles;
    s.badRatio = double(bad) / s.triangles;

    return s;
}

void MainWindow::MeshQuality()
{
    std::vector< std::pair<std::string, std::shared_ptr<ImplicitNode>> > shapes;

    shapes.push_back({"Sphere",                std::make_shared<SDFSphere>(1.0, Vector(0, 0, 0))});
    shapes.push_back({"Capsule",               std::make_shared<SDFCapsule>(1.0, Vector(-1, 0, 0), Vector(1, 0, 0))});
    shapes.push_back({"Torus",                 std::make_shared<SDFTorus>(2.0, 0.5, Vector(0, 0, 0))});
    shapes.push_back({"Box",                   std::make_shared<SDFBox>(1.0, 1.0, 1.0, Vector(0, 0, 0))});
    shapes.push_back({"Ellipsoid (pas 1-Lip)", std::make_shared<SDFEllipsoid>(1.0, 2.0, 1.0, Vector(0.0, 0.0, 0.0))});

    std::cout << "Forme, Résolution, Sommets, Triangles, $rho$-moyen, $rho$-minimum, Ratio mauvais, Erreur Moyenne, Erreur Maximale, Temps de calcul (ms)" << std::endl;

    const int resolutions[] = {64, 128, 256};

    for (const auto& [name, node] : shapes)
    {
        for (int res : resolutions)
        {
            AnalyticTree tree;
            tree.SetRoot(node);

            Mesh mesh;

            auto start = std::chrono::steady_clock::now();
            tree.Polygonize(res, mesh, Box(10));
            auto end = std::chrono::steady_clock::now();

            double ms = std::chrono::duration<double, std::milli>(end - start).count();

            MeshStats s = ComputeStats(mesh, *node);
            std::cout << name << ", " << res << ", " << s.vertices << ", " << s.triangles << ", "
                      << s.rhoMean << ", " << s.rhoMin << ", " << s.badRatio << ", "
                      << s.errorMean << ", " << s.errorMax << ", " << ms << std::endl;
        }
    }
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
