<h1>Robotic Arm with 3 DOF</h1>

 <!--### [YouTube Example](https://youtu.be/7eJexJVCqJo) EDIT-->

<h2>Description</h2>
Positioning the end effector of a Robotic Arm at a specific location in space, quarter of a sphere, through the simultaneous movement of three servomotors.
The system takes as input the variables x, y, z for the corresponding coordinates.

 ### Hardware
 *  The servos are connected in series, to a 3.3V power source and GND
 *  The signals for the servos are at digital pins: base-7, large link-5, small link-6
 *  The anode of the LED is connected to digital pin 12 through a resistor and the cathode to GND
 ### Software
 *  The Servo.h library is used
 *  To find the angle, e.g., f, the law of cosines is used (f=(A*A+B*B-C*C)/2*A*B)
 *  A, B are the adjacent sides of the angle and C is the opposite side
 ### Limitations
 *  The movement occurs along the axes: xx', y, z
 *  This system has a minimum possible distance from (0,0,0) of 4cm and a maximum of 13cm 
 *  The LED lights up when the coordinates are outside the workspace
*/
<br />


<h2>Languages Used</h2>

- <b>C++</b><br />


<h2>Environments Used </h2>
- <b><a href="https://www.tinkercad.com/things/llgpJ5cSB1u-robotic-arm-3dof">Tinkercad 3D Design</a></b><br />
- <b><a href="https://www.tinkercad.com/things/llgpJ5cSB1u-robotic-arm-3dof">Tinkercad Circuit + Code</a></b><br />
- <b>Arduino</b> <br />
- <b>Windows 10</b> 

<h2>Program walk-through:</h2>

<p align="center">
3D Design Pictures: <br/>
<img src="https://i.imgur.com/gWQomwe.png" height="100%" width="45%" alt="Front View"/>
<img src="https://i.imgur.com/nt2MHbg.png" height="45%" width="45%" alt="Upper Left View"/>
<img src="https://i.imgur.com/Noc0zAS.png" height="45%" width="45%" alt="Top View"/>
<img src="https://i.imgur.com/mCxs15b.png" height="45%" width="45%" alt="Back View"/>


<br />
Circuit: <br/>
<img src="https://i.imgur.com/N4z4cuP.png" height="100%" width="100%" alt="Circuit"/>

<br />
<br />
</p>

<!--
 ```diff
- text in red
+ text in green
! text in orange
# text in gray
@@ text in purple (and bold)@@
```
--!>
