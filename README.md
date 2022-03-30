# OpenGL_Exercises
Small Projects/ Exercices done by using OpenGL.

**5.8.1 Try to draw 2 triangles next to each other using glDrawArrays by adding more vertices to your data.**

![image](https://user-images.githubusercontent.com/72278818/160698998-de18a3a9-c295-4af6-a204-c5c986ce9405.png)

**I method:**

All data in one VBO, the same VAO and shader program.

![image](https://user-images.githubusercontent.com/72278818/160692731-ccb9a160-dee2-40af-9e28-768cfb9c9098.png)

**II method:**

Two different VAO and shader programs.

![image](https://user-images.githubusercontent.com/72278818/160692790-d2ddadce-123c-4383-8013-695cb6d3199b.png)

**5.8.2 Now create the same 2 triangles using two different VAOs and VBOs for their data.**

![image](https://user-images.githubusercontent.com/72278818/160699124-5565de93-c9e3-46c0-9eda-6dfbe2d27d10.png)

![image](https://user-images.githubusercontent.com/72278818/160699153-090670fd-3515-4127-aa12-2a11995ced69.png)

**5.8.3 Create two shader programs where the second program uses a different fragment shader that outputs the color yellow; drwa both triangles again where one outputes the color yellow.**

![image](https://user-images.githubusercontent.com/72278818/160704294-a54f95ec-1afe-4cf4-aaba-b25f4cf997dd.png)

![image](https://user-images.githubusercontent.com/72278818/160704463-ea4b4594-ceca-4bc5-9bf5-f103d02242ca.png)

**6.7.1 Adjust the vertex shader so that the triangle is upside down**

![image](https://user-images.githubusercontent.com/72278818/160831423-571cd3e8-0175-4729-ba8c-8bf9c8cd8c87.png)

![image](https://user-images.githubusercontent.com/72278818/160831471-b1fdb401-6f51-4a30-bd48-08e7ed0f2920.png)

**6.7.2 Specify a horizontal offset via a uniform and move triangle right side of the screen in the vertex shader using this offset value.**

![image](https://user-images.githubusercontent.com/72278818/160836070-ea39df24-31e0-45a9-a288-eeb353ad9c90.png)

![ezgif com-gif-maker (2)](https://user-images.githubusercontent.com/72278818/160836090-718efdfc-acaf-42d1-a9ef-2ee1aeef227e.gif)

**6.7.3 Output the vertex position to the fragment shader using the out keyword and set the fragment's color equal to this vertex position (see how even the vertex position values are interpolated across the triangle). Once you managed to do this; try to answer the following question: why is the bottom-left side of our triangle black?**

![image](https://user-images.githubusercontent.com/72278818/160845492-ba879388-4826-4ed2-9a82-2b5da90856f8.png)

![image](https://user-images.githubusercontent.com/72278818/160844660-2b4f277e-2f00-46cd-ad7b-ce302bf14e96.png)

The bottom-left side is black because X and Y are negative and there is no such a thing like a negative RGB colors, so it is by default black. You can see that if we go higher to the top green is lighter, because color of vertex is (0.0f, 1.0f, 0.0f) RGB. If we are going down we will have much darker color.

