/* 
 * Base code for CS 296 Software Systems Lab 
 * Department of Computer Science and Engineering, IIT Bombay
 * Instructor: Parag Chaudhuri
 */
#include "cs296_base.hpp"
#include "render.hpp"
#ifdef __APPLE__
	#include <GLUT/glut.h>
#else
	#include "GL/freeglut.h"
#endif
#include <cstring>
using namespace std;
#include "dominos.hpp"
namespace cs296
{
  /**  The is the constructor.
   * It constructs the world by setting up various objects and adding them to the world.
   */ 
  
  
  dominos_t::dominos_t()
  {


    //Ground
    /** b2Body* b1 \n
     * \brief pointer to the body. \n
     * VAR sim_t* sim \n
     * \brief pointer to the simulation */
    
    /** The following are initialised in the constructor. \n */


     //!The ground of the simulation
    b2Body* b1;  
    {
    
    
      b2EdgeShape shape;//Edge shape representing the ground
      shape.Set(b2Vec2(-90.0f, 0.0f), b2Vec2(90.0f, 0.0f));//end points of the ground
      b2BodyDef bd;
      b1 = m_world->CreateBody(&bd); //Adds ground to the world
      b1->CreateFixture(&shape, 0.0f); //Binds shape to the fixture
    }
          
    //!Top horizontal shelf
    {
      b2PolygonShape shape;//Shape representing the shelf carrying dominos
      shape.SetAsBox(6.0f, 0.25f);//Sets the shape as a square
	
      b2BodyDef bd;//Properties of the body
      bd.position.Set(-31.0f, 30.0f);//Sets the center of the body 
      b2Body* ground = m_world->CreateBody(&bd);//Adds body to the scene
      ground->CreateFixture(&shape, 0.0f);//Creates fixture of shape as above for colission
    }
    //!All the Dominos which topple 
    {
      b2PolygonShape shape;// The shape of dominos
      shape.SetAsBox(0.1f, 1.0f);// Sets shape as rectangle
	
      b2FixtureDef fd;// Properties of body
      fd.shape = &shape;//Sets the shape of body as defined above.
      fd.density = 20.0f;//Density setting
      fd.friction = 0.1f;//Friction setting
		
      for (int i = 0; i < 10; ++i)   // For loop for setting the train of 10 dominos
	{
	  b2BodyDef bd;
	  bd.type = b2_dynamicBody;
	  bd.position.Set(-35.5f + 1.0f * i, 31.25f); // Setting up dominos sequentially
	  b2Body* body = m_world->CreateBody(&bd);
	  body->CreateFixture(&fd);
	}
    }
      
    //!Another horizontal shelf supporting dominos
    
    {
      b2PolygonShape shape;// The shape of dominos
      shape.SetAsBox(7.0f, 0.25f, b2Vec2(-20.f,20.f), 0.0f);// Sets shape as rectangle
	
      b2BodyDef bd;
      bd.position.Set(1.0f, 6.0f);// Sets the position
      b2Body* ground = m_world->CreateBody(&bd);
      ground->CreateFixture(&shape, 0.0f);
    }
    
    //!The pendulum that knocks the dominos off
    
    {
      b2Body* b2;// Plank which acts as a pivot
      {
	b2PolygonShape shape;
	shape.SetAsBox(0.25f, 1.5f);
	  
	b2BodyDef bd;
	bd.position.Set(-36.5f, 28.0f);
	b2 = m_world->CreateBody(&bd);
	b2->CreateFixture(&shape, 10.0f);
      }
	
      b2Body* b4; // Bob
      {
	b2PolygonShape shape;
	shape.SetAsBox(0.25f, 0.25f); // The bob is a small square
	  
	b2BodyDef bd;
	bd.type = b2_dynamicBody;
	bd.position.Set(-40.0f, 33.0f); //Setting the initial position of bob
	b4 = m_world->CreateBody(&bd);
	b4->CreateFixture(&shape, 2.0f);
      }
	
      b2RevoluteJointDef jd;// Revolute joint whose one end is fixed 
      b2Vec2 anchor;
      anchor.Set(-37.0f, 40.0f); //Setting the point of revolution for pendulum bob
      jd.Initialize(b2, b4, anchor);
      m_world->CreateJoint(&jd);
    }
      
    //!The train of small spheres that fall into the bucket
    {
      b2Body* spherebody;// Defining how sphere should be like
	
      b2CircleShape circle;
      circle.m_radius = 0.5; // Setting the radius
	
      b2FixtureDef ballfd;
      ballfd.shape = &circle;
      ballfd.density = 1.0f;
      ballfd.friction = 0.0f; // Frictionless surface = > Pure sliding
      ballfd.restitution = 0.0f;
	
      for (int i = 0; i < 10; ++i) // for loop for generating the train of spheres
	{
	  b2BodyDef ballbd;
	  ballbd.type = b2_dynamicBody;
	  ballbd.position.Set(-22.2f + i*1.0, 26.6f); // Varying the position of sphere centre along line
	  spherebody = m_world->CreateBody(&ballbd);
	  spherebody->CreateFixture(&ballfd);
	}
    }
    //!The pulley system
    {
      b2BodyDef *bd = new b2BodyDef;// Creating a new variable bd of class b2BodyDef
      bd->type = b2_dynamicBody; //Various necessary initialisisations
      bd->position.Set(-10,15);
      bd->fixedRotation = true;
      
      //The open box
      b2FixtureDef *fd1 = new b2FixtureDef; //The horizontal part of the box
      fd1->density = 10.0;
      fd1->friction = 0.5;
      fd1->restitution = 0.f;
      fd1->shape = new b2PolygonShape;
      b2PolygonShape bs1;
      bs1.SetAsBox(2,0.2, b2Vec2(0.f,-1.9f), 0); //Initialising length and relative position
      fd1->shape = &bs1;
      b2FixtureDef *fd2 = new b2FixtureDef; //Vertical right part of the box
      fd2->density = 10.0;
      fd2->friction = 0.5;
      fd2->restitution = 0.f;
      fd2->shape = new b2PolygonShape;
      b2PolygonShape bs2;
      bs2.SetAsBox(0.2,2, b2Vec2(2.0f,0.f), 0); //Initialising length and relative position
      fd2->shape = &bs2;
      b2FixtureDef *fd3 = new b2FixtureDef; //Vertical left part of the box
      fd3->density = 10.0;
      fd3->friction = 0.5;
      fd3->restitution = 0.f;
      fd3->shape = new b2PolygonShape;
      b2PolygonShape bs3;
      bs3.SetAsBox(0.2,2, b2Vec2(-2.0f,0.f), 0); //Initialising length and relative position
      fd3->shape = &bs3;
       
      b2Body* box1 = m_world->CreateBody(bd); // Add three sides of the open box
      box1->CreateFixture(fd1);
      box1->CreateFixture(fd2);
      box1->CreateFixture(fd3);
      //The bar
      bd->position.Set(10,15);	
      fd1->density = 34.0;	  // Setting the counter weight
      b2Body* box2 = m_world->CreateBody(bd);
      box2->CreateFixture(fd1);
      // The pulley joint
      b2PulleyJointDef* myjoint = new b2PulleyJointDef();
      b2Vec2 worldAnchorOnBody1(-10, 15); // Anchor point on body 1 in world axis
      b2Vec2 worldAnchorOnBody2(10, 15); // Anchor point on body 2 in world axis
      b2Vec2 worldAnchorGround1(-10, 20); // Anchor point for ground 1 in world axis
      b2Vec2 worldAnchorGround2(10, 20); // Anchor point for ground 2 in world axis
      float32 ratio = 1.0f; // Define ratio
      myjoint->Initialize(box1, box2, worldAnchorGround1, worldAnchorGround2, box1->GetWorldCenter(), box2->GetWorldCenter(), ratio);
      m_world->CreateJoint(myjoint);
    }
    //!The revolving horizontal platform supporting the heavy ball
    {
      b2PolygonShape shape;
      shape.SetAsBox(2.2f, 0.2f);  // Sets shape of the revolving platform 
	
      b2BodyDef bd;
      bd.position.Set(14.0f, 14.0f); //Sets position of the revolving platfor,
      bd.type = b2_dynamicBody; // Makes the platform a dynamic body
      b2Body* body = m_world->CreateBody(&bd); // Adds body to the world
      b2FixtureDef *fd = new b2FixtureDef; // Creates a fixture defn
      fd->density = 1.f; // Gives properties to fixture defn
      fd->shape = new b2PolygonShape;
      fd->shape = &shape;
      body->CreateFixture(fd); // Binds fixture to body
      b2PolygonShape shape2; // The static platform to give reference to the revolute joint
      shape2.SetAsBox(0.2f, 2.0f); 
      b2BodyDef bd2;
      bd2.position.Set(14.0f, 16.0f); // Sets position of the reference platform
      b2Body* body2 = m_world->CreateBody(&bd2); // Adds reference platform to the world
      b2RevoluteJointDef jointDef; // New joint of type revolute
      jointDef.bodyA = body; // endpoint a: rotating platform 
      jointDef.bodyB = body2;// endpoint b: static reference platform 
      jointDef.localAnchorA.Set(0,0); // set both endpoints of the joint
      jointDef.localAnchorB.Set(0,0);
      jointDef.collideConnected = false;// prevent colission between reference platform and revolving platform
      m_world->CreateJoint(&jointDef);
    }
    //!The heavy sphere on the platform
    {
      b2Body* sbody;
      b2CircleShape circle;
      circle.m_radius = 1.0;
	
      b2FixtureDef ballfd;
      ballfd.shape = &circle;
      ballfd.density = 50.0f; // Heavy mass ball
      ballfd.friction = 0.0f; //Frictionless
      ballfd.restitution = 0.0f; // Completely inelastic ball
      b2BodyDef ballbd;
      ballbd.type = b2_dynamicBody;
      ballbd.position.Set(14.0f, 18.0f);
      sbody = m_world->CreateBody(&ballbd);
      sbody->CreateFixture(&ballfd);
    }
    //!The see-saw system at the bottom
    {
      //The triangle wedge
      b2Body* sbody;
      b2PolygonShape poly;
      b2Vec2 vertices[3];
      vertices[0].Set(-1,0);// set values of vertex vectors of triangle
      vertices[1].Set(1,0);
      vertices[2].Set(0,1.5);
      poly.Set(vertices, 3); // Set the polygon using vertex vectors 
      b2FixtureDef wedgefd;
      wedgefd.shape = &poly; //Set shape of the wedge to the polygon
      wedgefd.density = 10.0f; // Set density, etc other properties
      wedgefd.friction = 0.0f; // friction less
      wedgefd.restitution = 0.0f; // inelastic
      b2BodyDef wedgebd;
      wedgebd.position.Set(27.0f, 0.0f); // Set position of the wedge
      sbody = m_world->CreateBody(&wedgebd); //Add wedge to world
      sbody->CreateFixture(&wedgefd);
      //The plank on top of the wedge
      b2PolygonShape shape;
      shape.SetAsBox(15.0f, 0.2f); // Making it a plank using member function SetAsBox
      b2BodyDef bd2;
      bd2.position.Set(27.0f, 1.5f);
      bd2.type = b2_dynamicBody; // Declaring it is a dynamic body
      b2Body* body = m_world->CreateBody(&bd2); // Add body to the world
      b2FixtureDef *fd2 = new b2FixtureDef; // Give properties to the plank
      fd2->density = 1.f;
      fd2->shape = new b2PolygonShape;
      fd2->shape = &shape;
      body->CreateFixture(fd2);
      b2RevoluteJointDef jd; // Define joint between wedge and plank
      b2Vec2 anchor; 
      anchor.Set(27.0f, 1.5f); // Creating anchor for rotation point
      jd.Initialize(sbody, body, anchor); // Initialising the revolute joint 
      m_world->CreateJoint(&jd);
      
      //The light box on the right side of the see-saw
      
      b2PolygonShape shape2;
      shape2.SetAsBox(2.0f, 2.0f); // Making a box using member function of b2PolygonShape class
      b2BodyDef bd3;
      bd3.position.Set(40.0f, 2.0f);
      bd3.type = b2_dynamicBody; // Making it a dynamic body
      b2Body* body3 = m_world->CreateBody(&bd3);
      b2FixtureDef *fd3 = new b2FixtureDef;
      fd3->density = 0.01f; // A very light object
      fd3->shape = new b2PolygonShape;
      fd3->shape = &shape2; //setting the shape to shape2
      body3->CreateFixture(fd3);
    }
    
    //!		ELEMENTS ADDED BY US-
    
    //!The plank on which the cube lands after jumping in air
    {
    	b2PolygonShape shape;
    	shape.SetAsBox(4.0f, 0.2f); //Shape initialisation
    	b2BodyDef bd;
    	bd.position.Set(30.5f, 18.0f);//Position setup
    	b2Body* body=m_world->CreateBody(&bd);
    	b2FixtureDef *fd3 = new b2FixtureDef;
    	fd3->density = 10.0f;
    	fd3->shape = new b2PolygonShape;
    	fd3->shape=&shape;
    	body->CreateFixture(fd3); //Binding fixture to the body
    }
    //!The  pendulum rod
    {
    	b2PolygonShape shape;
     	shape.SetAsBox(0.2f, 10.0f);    // Defining lenght
      b2BodyDef bd2;
      bd2.position.Set(-20.0f, 12.0f);  // Position setup
      bd2.type = b2_dynamicBody;
      b2Body* body = m_world->CreateBody(&bd2);
      b2FixtureDef *fd2 = new b2FixtureDef;
      fd2->density = 10.f; 				//Initialising mass 
      fd2->shape = new b2PolygonShape;
      fd2->shape = &shape;
      body->CreateFixture(fd2); 
      b2RevoluteJointDef jd; 			//Setting up a revolute joint
      b2Vec2 anchor;
      anchor.Set(-20.0f, 16.0f); 		//Giving position to pivot point
      jd.Initialize(b1, body, anchor);  //Initialising the pivot point with its components
      m_world->CreateJoint(&jd);
    }
    //! The plank containing the Sphere to be set into rolling
    {
    	b2PolygonShape shape;
    	shape.SetAsBox(8.0f, 0.2f);// dimensions
    	b2BodyDef bd;
    	bd.position.Set(-29.f, 19.0f); //position
    	b2Body* body=m_world->CreateBody(&bd);
    	b2FixtureDef *fd3 = new b2FixtureDef;
    	fd3->density = 10.0f;
    	fd3->shape = new b2PolygonShape;
    	fd3->shape=&shape;
    	body->CreateFixture(fd3); //making it fixed
    }
    //! Rolling sphere 
    {
      b2Body* sbody;
      b2CircleShape circle;
      circle.m_radius = 2.0;//Set radius of ball
	
      b2FixtureDef ballfd;
      ballfd.shape = &circle; //Set shape of the ball to the above circle
      ballfd.density = 1.0f; //Set density
      ballfd.friction = 0.01f; //Set mass
      ballfd.restitution = .8f; //Sett coefficient of restitution
      b2BodyDef ballbd;
      ballbd.type = b2_dynamicBody; //Set to dynamic body
      ballbd.position.Set(-23.0f, 21.0f); //Set position
      sbody = m_world->CreateBody(&ballbd); //Add body to world
      sbody->CreateFixture(&ballfd); //Create fixture of circle shape
    }
     
    //! The last two planks
     {
    	b2PolygonShape shape;
    	shape.SetAsBox(4.0f, 0.2f); //Set the shape as a thin rect
    	b2BodyDef bd;
    	bd.position.Set(-41.5f, 15.0f); //First planks BodyDef. Give position
    	b2Body* body=m_world->CreateBody(&bd); //Create plank 1
	bd.position.Set(-35.5f, 10.0f); //Set position of plank 2
	b2Body* body2=m_world->CreateBody(&bd); //Create plank 2
    	b2FixtureDef *fd3 = new b2FixtureDef; //Create a fixture for colission properties
    	fd3->density = 10.0f;
    	fd3->shape = new b2PolygonShape;
    	fd3->shape=&shape;
    	body->CreateFixture(fd3); //Bind plank 1 to fixture 
	body->SetTransform(b2Vec2(-41.5f, 15.0f),-1.3f); //Rotate plank 1
	body2->CreateFixture(fd3);//Bind plank 2 to fixture
	body2->SetTransform(b2Vec2(-35.5f, 10.0f),1.3f);//Rotate plank 2
    }
    
    	
    //! \var 
  }
	
  sim_t *sim = new sim_t("Dominos", dominos_t::create);
  
}
