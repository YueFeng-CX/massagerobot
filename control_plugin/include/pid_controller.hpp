/*
 * pid_controller.hpp
 *
 *  Created on: 2023年6月21日
 *      Author: cx
 */

#ifndef INCLUDE_PID_CONTROLLER_HPP_
#define INCLUDE_PID_CONTROLLER_HPP_

#include <include/joint_controller.hpp>

namespace YF
{
	class PIDController : public JointsController
	{
	  public: PIDController(){}
	  public: virtual ~PIDController() override {}
	  public: virtual void execControlAlgorithm() override;

	  private:
	  	  double kp[JOINTNUMBER] = {200, 200, 200, 200, 200, 200};
	  	  double kd[JOINTNUMBER] = {10, 10, 10, 10, 10, 10};
	};

}

#endif /* INCLUDE_PID_CONTROLLER_HPP_ */
