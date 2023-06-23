/*
 * pid_controller.hpp
 *
 *  Created on: 2023年6月21日
 *      Author: cx
 */

#ifndef INCLUDE_PID_CONTROLLER_HPP_
#define INCLUDE_PID_CONTROLLER_HPP_

#include <gz/transport.hh>
#include <include/joint_controller.hpp>
#include <msgs/PidInterface.pb.h>

namespace YF
{
	class PIDController : public JointsController
	{
	  public: PIDController();
	  public: virtual ~PIDController() override {}
	  public: virtual void execControlAlgorithm() override;

	  public: void cbPidUserInterface(const msgs::PIDControllerTarget &_msgTarget);

	  private:
	  	  double kp[JOINTNUMBER] = {200, 200, 200, 100, 100, 100};
	  	  double kd[JOINTNUMBER] = {10, 10, 10, 10, 10, 10};
	  	  double targetPosition[6] = {0, 0, 0, 0, 0, 0};
	  	  ///brief communication topic
	  	  gz::transport::Node pidUserInterface;
	  	  std::string pidUserInterfaceTopic = "/pidUserInterfaceTopic";

	};

}

#endif /* INCLUDE_PID_CONTROLLER_HPP_ */
