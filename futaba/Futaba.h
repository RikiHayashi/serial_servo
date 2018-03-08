#include <array>
#include <numeric>
#include <chrono>
#include <thread>
#include <boost/asio.hpp>
#include <boost/thread.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

namespace Futaba {
	enum MODE {
		Normal = 0x01,
		Free = 0x00,
	};
	class Futaba {
		public:
			Futaba(std::string port, int baudrate = 460800) : serial_port_(io_srv_) {
				serial_port_.open(port);
				set_baudrate(baudrate);
				serial_port_.set_option(boost::asio::serial_port_base::parity(
							boost::asio::serial_port_base::parity::none));
				serial_port_.set_option(boost::asio::serial_port_base::flow_control(
							boost::asio::serial_port_base::flow_control::none));
				serial_port_.set_option(boost::asio::serial_port_base::stop_bits(
							boost::asio::serial_port_base::stop_bits::one));
				serial_port_.set_option(boost::asio::serial_port_base::character_size(8));
			}

			void set_baudrate(int baudrate) {
				serial_port_.set_option(boost::asio::serial_port::baud_rate(baudrate));
			}

			void set_mode(int id, MODE mode) {
				std::array<unsigned char, 9> buffer;
				buffer[0] = static_cast<unsigned char>(0xFA);
				buffer[1] = static_cast<unsigned char>(0xAF);
				buffer[2] = static_cast<unsigned char>(id);
				buffer[3] = static_cast<unsigned char>(0x00);
				buffer[4] = static_cast<unsigned char>(0x24);
				buffer[5] = static_cast<unsigned char>(0x01);
				buffer[6] = static_cast<unsigned char>(0x01);
				buffer[7] = static_cast<unsigned char>(mode);
				unsigned char sum = buffer[2];
				for(int i=3; i<buffer.size()-1;i++) sum = (unsigned char)(sum ^ buffer[i]);
				buffer[8] = static_cast<unsigned char>(sum);
				serial_port_.write_some(boost::asio::buffer(buffer, buffer.size()));
				std::this_thread::sleep_for(std::chrono::microseconds(250));
			}

			void set_angle(unsigned char id, double angle, double time) {
				int pos = angle * 100;
				int dt = time;
				std::array<unsigned char, 12> buffer;
				buffer[0] = static_cast<unsigned char>(0xFA);
				buffer[1] = static_cast<unsigned char>(0xAF);
				buffer[2] = static_cast<unsigned char>(id);
				buffer[3] = static_cast<unsigned char>(0x00);
				buffer[4] = static_cast<unsigned char>(0x1E);
				buffer[5] = static_cast<unsigned char>(0x04);
				buffer[6] = static_cast<unsigned char>(0x01);
				buffer[7] = static_cast<unsigned char>(pos & 0x00FF);
				buffer[8] = static_cast<unsigned char>((pos & 0xFF00) >> 8);
				buffer[9] = static_cast<unsigned char>(dt & 0x00FF);
				buffer[10] = static_cast<unsigned char>((dt & 0xFF00) >> 8);
				unsigned char sum = buffer[2];
				for(int i=3; i<buffer.size()-1;i++) sum = (unsigned char)(sum ^ buffer[i]);
				buffer[11] = static_cast<unsigned char>(sum);
				serial_port_.write_some(boost::asio::buffer(buffer, buffer.size()));
				std::this_thread::sleep_for(std::chrono::microseconds(250));
			}
			/*TODO get_angle 
			  short get_angle(unsigned char id) {
			  std::array<unsigned char, 7> buffer;
			  buffer[0] = static_cast<unsigned char>(0x07);
			  buffer[1] = static_cast<unsigned char>(0x03);
			  buffer[2] = static_cast<unsigned char>(0x00);
			  buffer[3] = static_cast<unsigned char>(id);
			  buffer[4] = static_cast<unsigned char>(0x2C);
			  buffer[5] = static_cast<unsigned char>(2);
			  buffer[6] = static_cast<unsigned char>(
			  std::accumulate(buffer.begin(), buffer.end() - 1, 0) & 0xFF);
			  serial_port_.write_some(boost::asio::buffer(buffer, buffer.size()));
			  std::this_thread::sleep_for(std::chrono::microseconds(250));
			  std::vector<unsigned char> readbuf(7);
			  serial_port_.read_some(boost::asio::buffer(readbuf, readbuf.size()));
			  return (readbuf[5] << 8) + readbuf[4];
			  }
			 */
			void servo_sleep(int t) {
				std::this_thread::sleep_for(std::chrono::milliseconds(t));
			}

			void servo_usleep(int t) {
				std::this_thread::sleep_for(std::chrono::microseconds(t));
			}

			void set_angle_wait_until(unsigned char id, double angle, double diff = 0.1) {
				set_angle(id, angle, 0.0);
				servo_usleep(250);
				while (abs(angle - (get_angle(id) / 100.0)) > diff) {
					servo_usleep(250);
				}
			}

		private:
			boost::asio::io_service io_srv_;
			boost::asio::serial_port serial_port_;
	};
}
