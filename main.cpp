#define CL_HPP_MINIMUM_OPENCL_VERSION   120
#define CL_HPP_TARGET_OPENCL_VERSION    120

#include <QCoreApplication>
#include <QDebug>

#include "CL/cl2.hpp"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    std::vector<cl::Platform> platforms;
    cl::Platform::get(&platforms);

    foreach(auto platform, platforms)
    {
        qDebug() << platform.getInfo<CL_PLATFORM_NAME>().data();
    }

    std::vector<cl::Device> devices;
    platforms.front().getDevices(CL_DEVICE_TYPE_GPU, &devices);

    foreach(auto device, devices)
    {
        qDebug() << device.getInfo<CL_DEVICE_NAME>().data();
    }

    return a.exec();
}
