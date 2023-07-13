import PySimpleGUI as sg
from PIL import Image
import os
import math


invisible = (0, 0, 0, 0)

def ok(x,y, max_x, max_y):
	return x>=0 and y>=0 and x<max_x and y<max_y

def generate(image):
	pixels = image.load()
	max_x = image.size[0]
	max_y = image.size[1]
	change_down = []
	change_right = []
	last_pixel_start = (-1,-1)
	last_pixel_length = 0
	last_pixel_colors = (-1, -1)

	for x in range(max_x+1):
		for y in range(max_y+1):
			pixel = pixels[x, y] if ok(x,y,max_x,max_y) else invisible
			new_pixel = pixels[x-1, y] if ok(x-1,y,max_x,max_y) else invisible
			if pixel != new_pixel:
				if (pixel, new_pixel) == last_pixel_colors:
					last_pixel_length+=1
				else:
					if last_pixel_length > 0:
						change_right.append((last_pixel_start[0], last_pixel_start[1], last_pixel_length, last_pixel_colors[0], last_pixel_colors[1]))
					last_pixel_start = (x,y)
					last_pixel_length = 1
					last_pixel_colors = (pixel, new_pixel)
			else:
				if last_pixel_length > 0:
					change_right.append((last_pixel_start[0], last_pixel_start[1], last_pixel_length, last_pixel_colors[0], last_pixel_colors[1]))
				last_pixel_start = (-1,-1)
				last_pixel_length = 0
				last_pixel_colors = (-1, -1)

			if last_pixel_length > 0 and y == max_y:
				change_right.append((last_pixel_start[0], last_pixel_start[1], last_pixel_length, last_pixel_colors[0], last_pixel_colors[1]))
	for y in range(max_y+1):
		for x in range(max_x+1):
			pixel = pixels[x, y] if ok(x,y,max_x,max_y) else invisible
			new_pixel = pixels[x, y-1] if ok(x,y-1,max_x,max_y) else invisible
			if pixel != new_pixel:
				if (pixel, new_pixel) == last_pixel_colors:
					last_pixel_length+=1
				else:
					if last_pixel_length > 0:
						change_down.append((last_pixel_start[0], last_pixel_start[1], last_pixel_length, last_pixel_colors[0], last_pixel_colors[1]))
					last_pixel_start = (x,y)
					last_pixel_length = 1
					last_pixel_colors = (pixel, new_pixel)
			else:
				if last_pixel_length > 0:
					change_down.append((last_pixel_start[0], last_pixel_start[1], last_pixel_length, last_pixel_colors[0], last_pixel_colors[1]))
				last_pixel_start = (-1,-1)
				last_pixel_length = 0
				last_pixel_colors = (-1, -1)

			if last_pixel_length > 0 and x == max_x:
				change_down.append((last_pixel_start[0], last_pixel_start[1], last_pixel_length, last_pixel_colors[0], last_pixel_colors[1]))
	return change_down, change_right



sg.theme('DarkAmber')


topdown_column = [[sg.Text("UpDown data")],[sg.Multiline("", key="-TopDown-", size=(40, 10), background_color="#a9a9a9", text_color="#00008b")]]
leftright_column = [[sg.Text("LeftRight data")],[sg.Multiline("", key="-LeftRight-", size=(40, 10), background_color="#a9a9a9", text_color="#00008b")]]

layout = [[sg.Text("Otevři obrázek pro vygenerování dat pro arduino"),
		sg.In(size=(25, 1), enable_events=True, key="-File-"),
		sg.FileBrowse(file_types=(("Image files", "*.jpg; *.png"),)),],
		[sg.Text("Vygenerovaná data")],
		[sg.Column(topdown_column), sg.VSeperator(), sg.Column(leftright_column)],
		[sg.Text("Barvy")],
		[sg.Multiline("", key="-Colors-", size=(90, 2), background_color="#a9a9a9", text_color="#00008b")],
		[sg.HSeparator()],
		[sg.Text("Kombinované")],
		[sg.Multiline("", key="-All-", size=(90, 10), background_color="#a9a9a9", text_color="#00008b")]
		]


window = sg.Window(title="Konzole - konvertor obrázků", layout=layout, margins=(20, 10))

while True:
	event, values = window.read()
	if event == "Exit" or event == sg.WIN_CLOSED:
		break
	if event == "-File-":
		file_name = values["-File-"]
		try:
			change_down, change_right = generate(Image.open(file_name))
			colors = {invisible: 255}
			color_count = 0
			result_down = "const PROGMEM uint8_t UD[][5] = {"
			for change in change_down:
				if change[3] not in colors:
					colors[change[3]] = color_count
					color_count+=1
				if change[4] not in colors:
					colors[change[4]] = color_count
					color_count+=1

				result_down += "{"+str(change[0])+","+str(change[1])+","+str(change[2])+","+str(colors[change[3]])+","+str(colors[change[4]])+"},"
			result_down = result_down[0:-1]+"};"

			result_right = "const PROGMEM uint8_t LR[][5] = {"
			for change in change_right:
				if change[3] not in colors:
					colors[change[3]] = color_count
					color_count+=1
				if change[4] not in colors:
					colors[change[4]] = color_count
					color_count+=1

				result_right += "{"+str(change[0])+","+str(change[1])+","+str(change[2])+","+str(colors[change[3]])+","+str(colors[change[4]])+"},"
			result_right = result_right[0:-1]+"};"
			
			color_export = "const PROGMEM color_t colors[] = {"
			for color in colors:
				if color == invisible:
					continue
				num_color = (round(math.floor(color[0]/8)) << 11) + (round(math.floor(color[1]/4)) << 5) + round(math.floor(color[2]/8))
				print(color)
				color_export += str(num_color) + ","
			color_export = color_export[0:-1]+"};"
			all_text = "Entity jmeno(LR, UD, colors, " + str(len(change_right)) +","+ str(len(change_down))+");"
			window.FindElement("-LeftRight-").Update(result_right)
			window.FindElement("-TopDown-").Update(result_down)
			window.FindElement("-Colors-").Update(color_export)
			window.FindElement("-All-").Update(all_text)

		except Exception as e:
			sg.popup_error(f'Chyba!', e)
		