testing:
	g++ -I./ -Ibackends/ -g -Wall -Wformat -c -o test.o test.cpp
	g++ -I./ -Ibackends/ -g -Wall -Wformat `pkg-config --cflags glfw3` -c -o imgui.o imgui.cpp
	g++ -I./ -Ibackends/ -g -Wall -Wformat `pkg-config --cflags glfw3` -c -o imgui_demo.o imgui_demo.cpp
	g++ -I./ -Ibackends/ -g -Wall -Wformat `pkg-config --cflags glfw3` -c -o imgui_draw.o imgui_draw.cpp
	g++ -I./ -Ibackends/ -g -Wall -Wformat `pkg-config --cflags glfw3` -c -o imgui_tables.o imgui_tables.cpp
	g++ -I./ -Ibackends/ -g -Wall -Wformat `pkg-config --cflags glfw3` -c -o imgui_widgets.o imgui_widgets.cpp
	g++ -I./ -Ibackends/ -g -Wall -Wformat `pkg-config --cflags glfw3` -c -o imgui_impl_glfw.o backends/imgui_impl_glfw.cpp
	g++ -I./ -Ibackends/ -g -Wall -Wformat `pkg-config --cflags glfw3` -c -o imgui_impl_opengl3.o backends/imgui_impl_opengl3.cpp
	g++ -o test test.o imgui.o imgui_demo.o imgui_draw.o imgui_tables.o imgui_widgets.o imgui_impl_glfw.o imgui_impl_opengl3.o -I./ -Ibackends/ -g -Wall -Wformat -lGL -lglfw -lrt -lm -ldl
	@echo Build complete!
