/*
* Copyright (c) 2006-2009 Erin Catto http://www.box2d.org
*
* This software is provided 'as-is', without any express or implied
* warranty.  In no event will the authors be held liable for any damages
* arising from the use of this software.
* Permission is granted to anyone to use this software for any purpose,
* including commercial applications, and to alter it and redistribute it
* freely, subject to the following restrictions:
* 1. The origin of this software must not be misrepresented; you must not
* claim that you wrote the original software. If you use this software
* in a product, an acknowledgment in the product documentation would be
* appreciated but is not required.
* 2. Altered source versions must be plainly marked as such, and must not be
* misrepresented as being the original software.
* 3. This notice may not be removed or altered from any source distribution.
*/

#ifndef REVOLUTE_H
#define REVOLUTE_H

class Revolute : public Test
{
public:
	Revolute()
	{
		b2Body* ground = NULL;
		{
			b2BodyDef bd;
			ground = m_world->CreateBody(&bd);

			b2EdgeShape shape;
			shape.Set(b2Vec2(-40.0f, 0.0f), b2Vec2(40.0f, 0.0f));
			ground->CreateFixture(&shape, 0.0f);
		}

		{
			b2CircleShape shape;
			shape.m_radius = 0.5f;

			b2BodyDef bd;
			bd.type = b2_dynamicBody;

			b2RevoluteJointDef rjd;

			bd.position.Set(-10.0f, 20.0f);
			b2Body* body = m_world->CreateBody(&bd);
			body->CreateFixture(&shape, 5.0f);

			float32 w = 100.0f;
			body->SetAngularVelocity(w);
			body->SetLinearVelocity(b2Vec2(-8.0f * w, 0.0f));

			rjd.Initialize(ground, body, b2Vec2(-10.0f, 12.0f));
			rjd.motorSpeed = 1.0f * b2_pi;
			rjd.maxMotorTorque = 10000.0f;
			rjd.enableMotor = false;
			rjd.lowerAngle = -0.25f * b2_pi;
			rjd.upperAngle = 0.5f * b2_pi;
			rjd.enableLimit = true;
			rjd.collideConnected = true;

			m_joint = (b2RevoluteJoint*)m_world->CreateJoint(&rjd);
		}

		{
			b2CircleShape circle_shape;
			circle_shape.m_radius = 3.0f;

			b2BodyDef circle_bd;
			circle_bd.type = b2_dynamicBody;
			circle_bd.position.Set(5.0f, 30.0f);

			b2Body* circle_body = m_world->CreateBody(&circle_bd);
			circle_body->CreateFixture(&circle_shape, 5.0f);

			b2PolygonShape polygon_shape;
			polygon_shape.SetAsBox(10.0f, 0.2f, b2Vec2 (-10.0f, 0.0f), 0.0f);

			b2BodyDef polygon_bd;
			polygon_bd.position.Set(20.0f, 10.0f);
			polygon_bd.type = b2_dynamicBody;
			polygon_bd.bullet = true;
			b2Body* polygon_body = m_world->CreateBody(&polygon_bd);
			polygon_body->CreateFixture(&polygon_shape, 2.0f);

			b2RevoluteJointDef rjd;
			rjd.Initialize(ground, polygon_body, b2Vec2(20.0f, 10.0f));
			rjd.lowerAngle = -0.25f * b2_pi;
			rjd.upperAngle = 0.0f * b2_pi;
			rjd.enableLimit = true;
			m_world->CreateJoint(&rjd);
		}
	}

	void Keyboard(unsigned char key)
	{
		switch (key)
		{
		case 'l':
			m_joint->EnableLimit(!m_joint->IsLimitEnabled());
			break;

		case 'm':
			m_joint->EnableMotor(!m_joint->IsMotorEnabled());
			break;
		}
	}

	void Step(Settings* settings)
	{
		Test::Step(settings);
		m_debugDraw.DrawString(5, m_textLine, "Keys: (l) limits, (m) motor");
		m_textLine += 15;
		//float32 torque1 = m_joint1->GetMotorTorque();
		//m_debugDraw.DrawString(5, m_textLine, "Motor Torque = %4.0f, %4.0f : Motor Force = %4.0f", (float) torque1, (float) torque2, (float) force3);
		//m_textLine += 15;
	}

	static Test* Create()
	{
		return new Revolute;
	}

	b2RevoluteJoint* m_joint;
};

#endif
