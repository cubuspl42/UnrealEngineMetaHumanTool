#include <iostream>
#include <filesystem>
#include <fstream>
#include <vector>

#include <msgpack.hpp>
#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>

#include <api/MetaHumanCreatorBodyAPI.h>

namespace fs = std::filesystem;

int main()
{
	// The default CWD seems to be UnrealEngine\Engine\Binaries\Win64 (set by the UE runtime?)
	const auto currentPath = fs::current_path();

	// Path to UnrealEngine\Engine 
	const auto enginePath = currentPath.parent_path().parent_path();

	const auto identityTemplatePath = enginePath / "Plugins\\MetaHuman\\MetaHumanCharacter\\Content\\Body\\IdentityTemplate";
	
	std::cout << "IdentityTemplate path:" << identityTemplatePath << std::endl;

	const auto mhcBodyApi = coretechlib::titan::api::MetaHumanCreatorBodyAPI::CreateMHCBodyApiStandalone(
		identityTemplatePath.string().c_str());

	const auto mhcBodyApiState = mhcBodyApi->CreateState();

	mhcBodyApi->Evaluate(*mhcBodyApiState);

	// av::ConstArrayView<float>, std::vector-alike
	const auto mesh = mhcBodyApiState->GetMesh(0);

	std::cout << "Mesh size: " << mesh.size() << "\n";

	// Dump mesh to MessagePack
	std::ofstream ofs("mesh.msgpack", std::ios::binary);

	if (!ofs) {
		std::cerr << "Failed to open mesh.msgpack for writing\n";
		return 1;
	}

	msgpack::pack(ofs, std::vector<float>{mesh.begin(), mesh.end()});

	ofs.close();
	
	std::cout << "Mesh dumped to mesh.msgpack\n";

	// Dump points to a PCL file
	if (mesh.size() % 3 != 0) {
		std::cerr << "Mesh size is not a multiple of 3, cannot interpret as point cloud.\n";
		return 1;
	}

	pcl::PointCloud<pcl::PointXYZ> cloud;

	cloud.width = static_cast<uint32_t>(mesh.size() / 3);
	cloud.height = 1;
	cloud.is_dense = false;
	cloud.points.resize(cloud.width);

	for (size_t i = 0; i < cloud.width; ++i) {
		cloud.points[i].x = mesh[i * 3 + 0];
		cloud.points[i].y = mesh[i * 3 + 1];
		cloud.points[i].z = mesh[i * 3 + 2];
	}

	if (pcl::io::savePCDFileBinary("mesh.pcd", cloud) == -1) {
		std::cerr << "Failed to write mesh.pcd\n";
		return 1;	
	}
	
	std::cout << "Mesh dumped to mesh.pcd\n";
}
