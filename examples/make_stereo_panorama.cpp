
#include <iostream>
#include <vector>
#include <cmath>
#include <fstream>

#include <gflags/gflags.h>

#include "stereo_panorama_tools.h"

using namespace sphericalsfm;
using namespace stereopanotools;

DEFINE_string(intrinsics, "", "Path to intrinsics (focal centerx centery)");
DEFINE_string(video, "", "Path to video or image search pattern like frame%06d.png");
DEFINE_string(output, "", "Path to output directory");
DEFINE_int32(width, 8192, "Width of output panorama");
DEFINE_bool(loop, true, "Trajectory is a closed loop");

int main( int argc, char **argv )
{
    gflags::ParseCommandLineFlags(&argc, &argv, true);
    
    double focal, centerx, centery;
    std::ifstream intrinsicsf( FLAGS_intrinsics );
    // intrinsicsf >> focal >> centerx >> centery;


    if (!intrinsicsf.is_open()) {
        std::cerr << "Error: Could not open intrinsics file: "
                << FLAGS_intrinsics << std::endl;
        return -1;
    }

    // Try reading values
    if (!(intrinsicsf >> focal >> centerx >> centery)) {
        std::cerr << "Error: Failed to read focal, centerx, centery from file: "
                << FLAGS_intrinsics << std::endl;
        return -1;
    }

    std::cout << "Intrinsics loaded successfully:\n"
            << "focal   = " << focal << "\n"
            << "centerx = " << centerx << "\n"
            << "centery = " << centery << std::endl;
    
    // std::cout << "intrinsics : " << focal << ", " << centerx << ", " << centery << "\n";

    Intrinsics intrinsics(focal,centerx,centery);

    make_stereo_panoramas( intrinsics, FLAGS_video, FLAGS_output, FLAGS_width, FLAGS_loop );
}
