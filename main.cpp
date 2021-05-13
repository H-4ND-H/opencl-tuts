#define CL_HPP_MINIMUM_OPENCL_VERSION   120
#define CL_HPP_TARGET_OPENCL_VERSION    120

#include <QCoreApplication>
#include <QDebug>
#include <QFile>

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

    cl::Context context(devices.front());

    QFile file("D:\\my_projects\\videos\\tutorials\\opencl\\kernel.cl");
    file.open(QFile::ReadOnly);
    auto arr = file.readAll();
    QString source(arr);

    cl_int err;
    cl::Program program(context, arr.toStdString(), CL_TRUE, &err);

    qDebug() << "Program: " << err;

    cl::Kernel kernel(program, "test", &err);

    qDebug() << "Kernel: " << err;

    cl::KernelFunctor<cl_int> functor(kernel);

    cl::CommandQueue queue(context, devices.front());

    cl::EnqueueArgs eargs(queue, cl::NDRange(5, 5));

    functor(eargs, 5);

    return a.exec();
}
