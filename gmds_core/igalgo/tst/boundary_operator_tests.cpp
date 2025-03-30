#include <catch2/catch_test_macros.hpp>
#include <gmds/ig/Mesh.h>
#include <gmds/ig/MeshDoctor.h>
#include <gmds/io/VTKWriter.h>
#include <gmds/io/VTKReader.h>
#include <gmds/igalgo/BoundaryOperator.h>
#include <gmds/igalgo/BoundaryOperator2D.h>
#include <iostream>
#include <gmds/io/IGMeshIOService.h>

using namespace gmds;


TEST_CASE("BoundaryOpClass: testBoundary2D", "[Boundary][2D]") {
    // WE WRITE
    gmds::Mesh m(gmds::MeshModel(DIM3 | F | N | F2N | N2F | E | E2N));

    std::string dir(TEST_SAMPLES_DIR);
    std::string vtk_file = dir + "/triangulated_quad.vtk";
    gmds::IGMeshIOService ioService(&m);
    gmds::VTKReader vtkReader(&ioService);
    vtkReader.setCellOptions(gmds::N | gmds::F);
    vtkReader.read(vtk_file);

    gmds::MeshDoctor doc(&m);
    doc.updateUpwardConnectivity();
    doc.buildBoundaryCells();

    gmds::BoundaryOperator2D bop(&m);

    REQUIRE(bop.isValid());

    int mark_edge_curve = m.newMark<gmds::Edge>();
    int mark_node_curve = m.newMark<gmds::Node>();

    bop.markCellsOnCurves(mark_edge_curve, mark_node_curve);

    int e = 0, n = 0;
    for (auto i : m.nodes()) {
        if (m.isMarked<gmds::Node>(i, mark_node_curve))
            n++;
    }
    for (auto i : m.edges()) {
        if (m.isMarked<gmds::Edge>(i, mark_edge_curve))
            e++;
    }

    REQUIRE(n != 0);
    REQUIRE(e != 0);

    m.unmarkAll<gmds::Edge>(mark_edge_curve);
    m.unmarkAll<gmds::Node>(mark_node_curve);
    m.freeMark<gmds::Edge>(mark_edge_curve);
    m.freeMark<gmds::Node>(mark_node_curve);
}
