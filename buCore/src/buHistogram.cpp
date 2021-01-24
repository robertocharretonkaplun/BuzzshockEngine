#include "buHistogram.h"
namespace buEngineSDK {
//#define errOut(x) if(0 != x) {std::std::cout << "Error de salida: " << x << std::std::endl; return x; }
  void 
  buHistogram::init() {
    // Get all platforms (Drivers)
  cl_uint num_platforms = 0;
  clGetPlatformIDs(0, nullptr, &num_platforms);

  Vector<cl_platform_id> all_platforms;
  all_platforms.resize(num_platforms);

  clGetPlatformIDs(num_platforms, &all_platforms[0], nullptr);

  String platform_name;
  String platform_version;
  String platform_vendor;
  String platform_extensions;
  platform_name.resize(255, '\0');
  platform_version.resize(255, '\0');
  platform_vendor.resize(255, '\0');
  platform_extensions.resize(1024, '\0');

  for (auto& platforms : all_platforms) {
    clGetPlatformInfo(platforms, CL_PLATFORM_VERSION, 255, &platform_version[0], nullptr);
    clGetPlatformInfo(platforms, CL_PLATFORM_NAME, 255, &platform_name[0], nullptr);
    clGetPlatformInfo(platforms, CL_PLATFORM_VENDOR, 255, &platform_vendor[0], nullptr);
    clGetPlatformInfo(platforms, CL_PLATFORM_EXTENSIONS, 1024, &platform_extensions[0], nullptr);

    std::cout << "Platform version: " << platform_version << std::endl;
    std::cout << "Platform name: " << platform_name << std::endl;
    std::cout << "Platform vendor: " << platform_vendor << std::endl;
    std::cout << "Platform extensions: " << platform_extensions << std::endl;
  }

  cl_platform_id selected_platform = all_platforms[0];

  cl_uint numDevices = 0;
  clGetDeviceIDs(selected_platform, CL_DEVICE_TYPE_ALL, 0, nullptr, &numDevices);

  Vector<cl_device_id> all_devices;
  all_devices.resize(numDevices);

  clGetDeviceIDs(selected_platform,
                        CL_DEVICE_TYPE_ALL,
                        numDevices,
                        &all_devices[0], 
                        nullptr);

  String device_name;
  String device_vendor;
  String driver_version;
  String device_profile;
  String device_version;
  String device_extensions;
  String device_platform;
  String device_double_fp_config;
  device_name.resize(255, '\0');
  device_vendor.resize(255, '\0');
  driver_version.resize(255, '\0');
  device_profile.resize(255, '\0');
  device_version.resize(255, '\0');
  device_extensions.resize(2048, '\0');
  //device_platform.resize(2048, '\0');
  device_double_fp_config.resize(1024, '\0');

  for (auto& device : all_devices) {
    clGetDeviceInfo(device, CL_DEVICE_NAME, 255, &device_name[0], nullptr);
    clGetDeviceInfo(device, CL_DEVICE_VENDOR, 255, &device_vendor[0], nullptr);
    clGetDeviceInfo(device, CL_DRIVER_VERSION, 255, &driver_version[0], nullptr);
    clGetDeviceInfo(device, CL_DEVICE_PROFILE, 255, &device_profile[0], nullptr);
    clGetDeviceInfo(device, CL_DEVICE_VERSION, 255, &device_version[0], nullptr);
    clGetDeviceInfo(device, CL_DEVICE_EXTENSIONS, 2048, &device_extensions[0], nullptr);
    //clGetDeviceInfo(device, CL_DEVICE_PLATFORM, 2048, &device_platform[0], nullptr);
    clGetDeviceInfo(device, CL_DEVICE_DOUBLE_FP_CONFIG, 1024, &device_double_fp_config[0], nullptr);

    std::cout << "Device name: " << device_name << std::endl;
    std::cout << "Device vendor: " << device_vendor << std::endl;
    std::cout << "Driver version: " << driver_version << std::endl;
    std::cout << "Device profile: " << device_profile << std::endl;
    std::cout << "Device version: " << device_version << std::endl;
    std::cout << "Device extensions: " << device_extensions << std::endl;
    //std::cout << "Device platform: " << device_platform << std::endl;
    std::cout << "Device double fp config: " << device_double_fp_config << std::endl;
  }

  cl_device_id selected_device = all_devices[0];

  cl_int error;
  cl_context context = clCreateContext(nullptr, 1, &selected_device, nullptr, nullptr, &error);
  //errOut(error);

  String kernel_code = "void kernel simple_add(global const int* A,"
                                              "global const int* B,"
                                              "global int* C) {"
                          "int id = get_global_id(0);"
                          "C[id] = A[id] + B[id];"
                          "};";

  const char** code = (const char**)new char[1];
  code[0] = kernel_code.c_str();
  

  size_t codeSize = kernel_code.length();

  cl_program program = clCreateProgramWithSource(context, 1, code, &codeSize, &error);
  //errOut(error);

  clBuildProgram(program, 1, &selected_device, nullptr, nullptr, nullptr);

  cl_command_queue command_queue = clCreateCommandQueueWithProperties(context, selected_device, 0, &error);
  //errOut(error);

  cl_kernel simple_Add = clCreateKernel(program, "simple_add", &error);
 // errOut(error);

  cl_mem buffer_A = clCreateBuffer(context, CL_MEM_READ_WRITE, sizeof(int) * 10, nullptr, &error);
 // errOut(error);

  cl_mem buffer_B = clCreateBuffer(context, CL_MEM_READ_WRITE, sizeof(int) * 10, nullptr, &error);
 // errOut(error);

  cl_mem buffer_C = clCreateBuffer(context, CL_MEM_READ_WRITE, sizeof(int) * 10, nullptr, &error);
  //errOut(error);

  int A[] = { 0,1,2,3,4,5,6,7,8,9 };
  int B[] = { 0,1,2,0,1,2,0,1,2,0 };

  clEnqueueWriteBuffer(command_queue, buffer_A, CL_TRUE, 0, sizeof(int) * 10, A, 0, nullptr, nullptr);
  clEnqueueWriteBuffer(command_queue, buffer_B, CL_TRUE, 0, sizeof(int) * 10, B, 0, nullptr, nullptr);
  
  clSetKernelArg(simple_Add, 0, sizeof(cl_mem), (void*)&buffer_A);
  clSetKernelArg(simple_Add, 1, sizeof(cl_mem), (void*)&buffer_B);
  clSetKernelArg(simple_Add, 2, sizeof(cl_mem), (void*)&buffer_C);

  size_t global_work = 10;
  clEnqueueNDRangeKernel(command_queue, simple_Add, 1, nullptr, &global_work, nullptr, 0, nullptr, nullptr);

  clFinish(command_queue);

  int C[10];

  clEnqueueReadBuffer(command_queue, buffer_C, CL_TRUE, 0, sizeof(int) * 10, C, 0, nullptr, nullptr);

  std::cout << "Results: ";

  for (int i : C) {
    std::cout << i << std::endl;
  }
  }

  void
  buHistogram::drawUI(String _windowName, String _description) {
    ImGui::Begin(_windowName.c_str());
    ImGui::PlotHistogram(_description.c_str(), arr, sizeof(arr), 0, nullptr, 0.0f, 1.0f, ImVec2(0, 80));
    ImGui::End();
  }
}