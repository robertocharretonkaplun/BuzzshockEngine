#include "buHistogram.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
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

    String kernel_code = "void kernel Histogram(global const int* RED,"
                                                "global const int* GREEN,"
                                                "global const int* BLUE,"
                                                "global const int* ALPHA,"
                                                "global int* oRED,"
                                                "global int* oGREEN,"
                                                "global int* oBLUE,"
                                                "global int* oALPHA) {"
                                                  "int id = get_global_id(0);"
                                                  "atomic_add(&oRED[RED[id]],1);"
                                                  "atomic_add(&oGREEN[GREEN[id]],1);"
                                                  "atomic_add(&oBLUE[BLUE[id]],1);"
                                                  "atomic_add(&oALPHA[ALPHA[id]],1);"
                                                "};";

    const char** code = (const char**)new char[1];
    code[0] = kernel_code.c_str();
    

    size_t codeSize = kernel_code.length();

    cl_program program = clCreateProgramWithSource(context, 1, code, &codeSize, &error); 
    //errOut(error);

    clBuildProgram(program, 1, &selected_device, nullptr, nullptr, nullptr);

    cl_command_queue command_queue = clCreateCommandQueueWithProperties(context, selected_device, 0, &error);
    //errOut(error);

    cl_kernel Histogram = clCreateKernel(program, "Histogram", &error);
    // errOut(error);

    int32 Channels, x, y;
    unsigned char* image = stbi_load("Data/Textures/927310.jpg", &x, &y, &Channels, 4);

    int32 pixelSize = x * y;

    cl_mem buffer_red = clCreateBuffer(context, CL_MEM_READ_WRITE, sizeof(int) * pixelSize, nullptr, &error);
    // errOut(error);

    cl_mem buffer_green = clCreateBuffer(context, CL_MEM_READ_WRITE, sizeof(int) * pixelSize, nullptr, &error);
    // errOut(error);

    cl_mem buffer_blue = clCreateBuffer(context, CL_MEM_READ_WRITE, sizeof(int) * pixelSize, nullptr, &error);
    cl_mem buffer_alpha = clCreateBuffer(context, CL_MEM_READ_WRITE, sizeof(int) * pixelSize, nullptr, &error);
    //errOut(error);
    cl_mem buffer_outRed = clCreateBuffer(context, CL_MEM_READ_WRITE, sizeof(int) * 256, nullptr, &error);
    cl_mem buffer_outGreen = clCreateBuffer(context, CL_MEM_READ_WRITE, sizeof(int) * 256, nullptr, &error);
    cl_mem buffer_outBlue = clCreateBuffer(context, CL_MEM_READ_WRITE, sizeof(int) * 256, nullptr, &error);
    cl_mem buffer_outAlpha = clCreateBuffer(context, CL_MEM_READ_WRITE, sizeof(int) * 256, nullptr, &error);




    for (uint32 i = 0; i < x; i++) {
      for (uint32 j = 0; j < y; j++) {
        SIZE_T index = Channels * (j * x + i);

        UBYTE r = image[index + 0];
        UBYTE g = image[index + 1];
        UBYTE b = image[index + 2];
        UBYTE a = image[index + 3];

        m_red.push_back(r);
        m_green.push_back(g);
        m_blue.push_back(b);
        m_alpha.push_back(a);
      }
    }

    stbi_image_free(image);
    int outRed[256] = { 0 };
    int outGreen[256] = { 0 };
    int outBlue[256] = { 0 };
    int outAlpha[256] = { 0 };
    clEnqueueWriteBuffer(command_queue, buffer_red, CL_TRUE, 0, sizeof(int) * pixelSize, m_red.data(), 0, nullptr, nullptr);
    clEnqueueWriteBuffer(command_queue, buffer_green, CL_TRUE, 0, sizeof(int) * pixelSize, m_green.data(), 0, nullptr, nullptr);
    clEnqueueWriteBuffer(command_queue, buffer_blue, CL_TRUE, 0, sizeof(int) * pixelSize, m_blue.data(), 0, nullptr, nullptr);
    clEnqueueWriteBuffer(command_queue, buffer_alpha, CL_TRUE, 0, sizeof(int) * pixelSize, m_alpha.data(), 0, nullptr, nullptr);
    clEnqueueWriteBuffer(command_queue, buffer_outRed, CL_TRUE, 0, sizeof(int) * 256, outRed, 0, nullptr, nullptr);
    clEnqueueWriteBuffer(command_queue, buffer_outGreen, CL_TRUE, 0, sizeof(int) * 256, outGreen, 0, nullptr, nullptr);
    clEnqueueWriteBuffer(command_queue, buffer_outBlue, CL_TRUE, 0, sizeof(int) * 256, outBlue, 0, nullptr, nullptr);
    clEnqueueWriteBuffer(command_queue, buffer_outAlpha, CL_TRUE, 0, sizeof(int) * 256, outAlpha, 0, nullptr, nullptr);
    
    clSetKernelArg(Histogram, 0, sizeof(cl_mem), (void*)&buffer_red);
    clSetKernelArg(Histogram, 1, sizeof(cl_mem), (void*)&buffer_green);
    clSetKernelArg(Histogram, 2, sizeof(cl_mem), (void*)&buffer_blue);
    clSetKernelArg(Histogram, 3, sizeof(cl_mem), (void*)&buffer_alpha);
    clSetKernelArg(Histogram, 4, sizeof(cl_mem), (void*)&buffer_outRed);
    clSetKernelArg(Histogram, 5, sizeof(cl_mem), (void*)&buffer_outGreen);
    clSetKernelArg(Histogram, 6, sizeof(cl_mem), (void*)&buffer_outBlue);
    clSetKernelArg(Histogram, 7, sizeof(cl_mem), (void*)&buffer_outAlpha);

    size_t global_work = pixelSize;


    clEnqueueNDRangeKernel(command_queue, Histogram, 1, nullptr, &global_work, nullptr, 0, nullptr, nullptr);

    clFinish(command_queue);

    clEnqueueReadBuffer(command_queue, buffer_outRed, CL_TRUE, 0, sizeof(int) *   256, outRed, 0, nullptr, nullptr);
    clEnqueueReadBuffer(command_queue, buffer_outGreen, CL_TRUE, 0, sizeof(int) * 256, outGreen, 0, nullptr, nullptr);
    clEnqueueReadBuffer(command_queue, buffer_outBlue, CL_TRUE, 0, sizeof(int) *  256, outBlue, 0, nullptr, nullptr);
    clEnqueueReadBuffer(command_queue, buffer_outAlpha, CL_TRUE, 0, sizeof(int) * 256,outAlpha, 0, nullptr, nullptr);

    std::cout << std::endl;
    int32 maxValRed = 0;
    int32 maxValGreen = 0;
    int32 maxValBlue = 0;
    int32 maxValAlpha = 0;
    for (uint32 i = 0; i < 256; i++) {
      if (outRed[i] > maxValRed) {
        maxValRed = outRed[i];
      }
      if (outGreen[i] > maxValGreen) {
        maxValGreen = outGreen[i];
      }
      if (outBlue[i] > maxValBlue) {
        maxValBlue = outBlue [i] ;
      }
      if (outAlpha[i] > maxValAlpha) {
        maxValAlpha = outAlpha[i];
      }
    }
    for (uint32 i = 0; i < 256; i++)
    {
      m_r.push_back((float)outRed[i] / maxValRed);
      m_g.push_back((float)outGreen[i] / maxValGreen);
      m_b.push_back((float)outBlue[i] / maxValBlue);
      m_a.push_back((float)outAlpha[i] / maxValAlpha);
    }
  }

  void
  buHistogram::drawUI(String _windowName, String _description) {
    ImGui::Begin(_windowName.c_str());
    ImGui::PlotHistogram("Red", &m_r[0], m_r.size(), 0, nullptr, 0.0f, 1.0f, ImVec2(0, 80));
    ImGui::PlotHistogram("Green", &m_g[0], m_g.size(), 0, nullptr, 0.0f, 1.0f, ImVec2(0, 80));
    ImGui::PlotHistogram("Blue", &m_b[0], m_b.size(), 0, nullptr, 0.0f, 1.0f, ImVec2(0, 80));
    ImGui::PlotHistogram("Alpha", &m_a[0], m_a.size(), 0, nullptr, 0.0f, 1.0f, ImVec2(0, 80));
    ImGui::End();
  }
}