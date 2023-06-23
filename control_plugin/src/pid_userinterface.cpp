/*
 * pid_userinterface.cpp
 *
 *  Created on: 2023年6月23日
 *      Author: cx
 */


#include <iostream>
#include <csignal>
#include <gz/transport.hh>
#include <include/pid_userinterface.hpp>
#include <msgs/PidInterface.pb.h>

#define TIP_ROBOTSTATE  std::cout <<"========== PID target user interface========== " << std::endl \
                                  <<    "option = [ target = 1,  others TODO, " << std::endl \
                                  << "0 (Exit) ] " << std::endl \
                                  << "=========================================" << std::endl \
                                  << "Number = ";

#define TIP_STR(str) std::cout << str << std::endl;

#define INPUT_INFO(var, str)  while(! (std::cin >> var)) \
                              {\
								  TIP_STR(str) \
								  std::cin.clear(); \
								  std::cin.ignore(512, '\n'); \
                              }


/// TODO, move config to a YAML like file
namespace CONFIG
{
#define JOINTNUMBER 6
	uint64_t JointNumber = JOINTNUMBER;
}

enum OPTION
{
	target = 1
};

int main(int argc, char **argv)
{
	// Create a transport node and advertise a topic.
	gz::transport::Node node;
	std::string topic = "/pidUserInterfaceTopic";
	auto pub = node.Advertise<msgs::PIDControllerTarget>(topic);
	if (!pub) {
		std::cerr << "Error advertising topic [" << topic << "]" << std::endl;
		return -1;
	}

	// Prepare the message.
	int64_t input = -1;
	double targetbuffer[JOINTNUMBER] = {0, 0, 0, 0, 0, 0};
	msgs::PIDControllerTarget msgPID;
	for(int i = 0; i < CONFIG::JointNumber; i++)
	{
		msgPID.add_pidtarget(0);
	}

	// Terminal command input
	TIP_ROBOTSTATE;
	while (input != 0)
	{
		INPUT_INFO(input, "")
		switch (input)
		{
			case OPTION::target:
			{
				std::cout << "6 targets inputs (space delimiter): ";
				for(int i = 0; i < CONFIG::JointNumber; i++)
				{
					INPUT_INFO(targetbuffer[i], "Bad number input, try again :");
					msgPID.set_pidtarget(i, targetbuffer[i]);
				}
				std::cout << "Publish target data : " << msgPID.pidtarget(0) << ",  " << msgPID.pidtarget(1)
				          << ",  " << msgPID.pidtarget(2) << ",  " << msgPID.pidtarget(3)
						  << ",  " << msgPID.pidtarget(4) << ",  " << msgPID.pidtarget(5)
						  << std::endl;
			}
				break;
			default:
				std::cout << "Wrong input, try again. " << std::endl;
				TIP_ROBOTSTATE;
				continue;
		}
		pub.Publish(msgPID);
		TIP_ROBOTSTATE;
	}
	std::cout << "Programme End !" << std::endl;

  return 0;
}
