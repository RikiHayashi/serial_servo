#include <iostream>
#include <vector>
#include <string>
#include <boost/asio.hpp>
#include <chrono>
#include <thread>
#include <boost/thread/thread.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

using namespace std;

class ServoTest{
	public:
		unsigned char ID;
		std::vector<char> buffer;
		std::vector<char> buffer2;
		short angle;
		short stime;
		short sum;
	public:
		ServoTest();
		void ConnectServo();
		void Command();
	private:
		boost::asio::io_service io_srv;
		boost::asio::serial_port port;
};

ServoTest::ServoTest() : port(io_srv)
{
	ID = 0x00;
	angle = 0.0;
	stime = 0.0;
	sum = 0;

	ConnectServo();
}

void ServoTest::ConnectServo()
{
	std::string portname = "/dev/ttyUSB0";
	const int baudrate = 115200;

	port.open(portname);
	port.set_option(boost::asio::serial_port_base::baud_rate(baudrate));
	port.set_option(boost::asio::serial_port_base::parity(boost::asio::serial_port_base::parity::none));
	port.set_option(boost::asio::serial_port_base::flow_control(boost::asio::serial_port_base::flow_control::none));
	port.set_option(boost::asio::serial_port_base::stop_bits(boost::asio::serial_port_base::stop_bits::one));

	std::cout<<"connect"<<std::endl;
	std::this_thread::sleep_for(std::chrono::milliseconds(1000));
}

void ServoTest::Command()
{
	std::cout<<"unlock..."<<std::endl;
	buffer.resize(8);
	buffer2.resize(16);
	buffer[0] = (unsigned char)0x08;
	buffer[1] = (unsigned char)0x04;
	buffer[2] = (unsigned char)0x00;
	buffer[3] = (unsigned char)0x05;
	buffer[4] = (unsigned char)0x00;
	buffer[5] = (unsigned char)0x28;
	buffer[6] = (unsigned char)0x01;

	for(int i=0;i<buffer.size()-1;i++)
		sum += buffer[i];
	buffer[7] = (unsigned char)(sum&0x00FF);
	for(int i = 0; i < buffer.size(); i++) {
		std::cout << (int)buffer[i] << " ";
	}
	std::cout << std::endl;

	std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	port.write_some(boost::asio::buffer(buffer,buffer.size()));
	std::cout<<"write..."<<std::endl;
	std::this_thread::sleep_for(std::chrono::milliseconds(10000));
	port.read_some(boost::asio::buffer(buffer2,buffer2.size()));
	std::cout<<"read..."<<std::endl;
	std::this_thread::sleep_for(std::chrono::milliseconds(1000));

	buffer.clear();
	
	port.close();

}

int main(int argc,char *argv[])
{
	ServoTest ST;

	ST.Command();
	
	return 0;
}
