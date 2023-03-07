from PIL import Image
import numpy as np

im = Image.open("static/input_image_1.jpg").convert('L') # 8-bit Mode convert

pixel_data = np.asarray(im)
print(pixel_data)
print(pixel_data.shape)
np.savetxt('pixel_data.csv', pixel_data)