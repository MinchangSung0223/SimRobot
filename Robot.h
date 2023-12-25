#ifndef ROBOT_SETUP_H
#define ROBOT_SETUP_H

#include <RobotSimulator/b3RobotSimulatorClientAPI.h>
#include "LinearMath/btVector3.h"
#include "LinearMath/btQuaternion.h"
#include "Bullet3Common/b3HashMap.h"

#include <LR/include/type.h>
#include <Eigen/Dense>
#include <vector>
using namespace Eigen;
using namespace std;

class Robot
{
private:
	class b3RobotSimulatorClientAPI* sim;
	int robot_id;
	int actuated_joint_num;
	int eef_num;
	int line_id;
	int draw_cnt =0 ;
	JVec q;
	JVec q_dot;
	JVec q_ddot;
	int draw_id_x;
	int draw_id_y;
	int draw_id_z;
	vector<int> actuated_joint_id;
	vector<string> actuated_joint_name;
   
public:
	Robot(class b3RobotSimulatorClientAPI* sim,int robot_id);
	Robot( class b3RobotSimulatorClientAPI* sim, int robot_id,JVec q0);
	void InitializeRobot();
	JVec get_q();
	JVec get_q_dot();
	SE3 get_eef_pose();
	void reset_q(JVec q);	
	void set_q(JVec q );
	void set_torques(JVec torques ,JVec  max_torques);
	Vector3d get_eef_forces();
	Vector3d get_eef_moments();
	void apply_ext_forces(Vector3d forces);
	void apply_ext_torques(Vector3d torques);
	int get_robot_id(){
		return this->robot_id;
	};
	int get_eef_num(){
		return this->eef_num;
	};
	JVec calc_inverse_dynamics();
	void draw_eef_T(float line_length,float line_width);
	virtual ~Robot();

};
#endif  //ROBOT_SETUP_H
