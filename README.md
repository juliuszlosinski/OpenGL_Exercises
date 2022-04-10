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

**7.8.1 Make sure only the happy face looks in the other/reverse direction by changing the fragment shader.**

![image](https://user-images.githubusercontent.com/72278818/161201544-72a53c47-cb6b-47df-962c-fd82bc3d8003.png)

![image](https://user-images.githubusercontent.com/72278818/161201445-dce5ee94-cb6a-4030-9b81-f42e3488171b.png)

**7.8.2 Experiment with different texture wrapping methods by specyfing texture coordinates in the range 0.0f to 2.0f instead of 0.0f to 1.0f. See if you can experiment with other wrapping methods as well. See if you can display 4 smiley faces on a single container image clamped at its edge: solution, result. See if you can experiment with other wrapping methods as well.**

![image](https://user-images.githubusercontent.com/72278818/161262775-782cb90a-13cb-4549-bb56-dddf4cb5b727.png)

![image](https://user-images.githubusercontent.com/72278818/161210934-b8e24cc3-c365-4401-9f0c-4789a58a9cdd.png)

**7.8.3 Try to display only the center pixels of the texture image on the rectagnle in such a way thath the individual pixels are getting visible by changing the texture coordinates. Try to set the texture filtering method to GL_NEAREST to see the pixels more clearly.**

![image](https://user-images.githubusercontent.com/72278818/161262983-d7b3b6a6-f848-4387-9b36-e57dfc774601.png)

![image](https://user-images.githubusercontent.com/72278818/161262369-71e09d9b-794c-4a9b-adc5-0d91a16441f9.png)

**7.8.4 Use a uniform variable as the mix function's third parameter to vary the amount the two texture are visible. Use the up and down arrow keys to change how much the container or the smiley facey is visible.**

![image](https://user-images.githubusercontent.com/72278818/161266809-9c2c178e-dec0-43cd-8bc0-e0b7f263bf6d.png)

![ezgif com-gif-maker (3)](https://user-images.githubusercontent.com/72278818/161266710-5a9d0f40-5151-42df-9224-e3725a6e555a.gif)

**8.19.1 Using the last transformation on the container, try switching the order around by first rotating and then translating. See what happens and try to reason why this happens.**

![image](https://user-images.githubusercontent.com/72278818/161394759-7d884a3b-45d3-4477-91b3-f62a82a7d5be.png)

![ezgif com-gif-maker (4)](https://user-images.githubusercontent.com/72278818/161394659-655d2472-b115-4434-ab51-07f5553b19f7.gif)

**8.19.2 Try drawing a second container with another call to glDrawElements but place it at a
different position using transformations only. Make sure this second container is placed at
the top-left of the window and instead of rotating, scale it over time (using the sin function
is useful here; note that using sin will cause the object to invert as soon as a negative scale
is applied)**

![image](https://user-images.githubusercontent.com/72278818/161396219-83b73a6d-f30c-4b40-b6f8-e1cf791347fe.png)

![ezgif com-gif-maker (5)](https://user-images.githubusercontent.com/72278818/161396290-423cd20f-3e2d-4a76-989d-c90e9430e452.gif)

**9.9.1 Try experimenting with the FoV and aspect-ratio parameters of GLM's projection function. See if you can figure out how those affect the perspective frustum.**

![image](https://user-images.githubusercontent.com/72278818/161443695-cdccb646-af6f-45d6-8dcb-753cd2bccb2d.png)

![ezgif com-gif-maker (7)](https://user-images.githubusercontent.com/72278818/161443664-37318377-80fe-4b7c-af7a-ccb641a99e98.gif)

![ezgif com-gif-maker (9)](https://user-images.githubusercontent.com/72278818/161588920-4569ed73-37fb-4628-b327-6b1cc81facf0.gif)

**9.9.2 Play with view matrix by translating in several directions and see how the scene changes. Think of the view matrix as a camera object.**

![image](https://user-images.githubusercontent.com/72278818/161518264-a42d4d34-18df-47b8-9af8-2768a6369307.png)

![ezgif com-gif-maker (8)](https://user-images.githubusercontent.com/72278818/161518203-5b765058-9280-4d46-8b5f-c69d7e62f41b.gif)

**9.9.3 Try make every 3rd container (including the 1st) rotate over time, while leaving the other containers static using just the model matrix.**

![image](https://user-images.githubusercontent.com/72278818/161519796-49d997a7-bb77-474f-8523-8d95ecb65d6a.png)

![ezgif com-gif-maker (10)](https://user-images.githubusercontent.com/72278818/161522610-0c8ded73-504c-4a40-a0dc-ffff37db969b.gif)

**10.4.1 See if you can transform the camera class in such a way that is becomes a true fps camera where you cannot fly; you can only look around while staying on the xz plane.**

![image](https://user-images.githubusercontent.com/72278818/162618192-ff636eea-39b4-4a69-8603-116774afa1d4.png)

![ezgif com-gif-maker (12)](https://user-images.githubusercontent.com/72278818/162618240-e99771d6-7362-42f9-a7fb-d80a2d02a3fc.gif)
