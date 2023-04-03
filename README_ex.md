***Copyright** Lazar Cristian-Stefan 314CA 2022-2023*

[//]: # (This is a Markdown source file, so I hope you understand that putting
in line breaks at column 80 can break the syntax \(Unless there's some "continue
from the next line" tag I'm unaware of; I am pretty new to Markdown\). I'll do it
for comments, but not for the code.)

# ECy - image editor

ECy is an image editor, written in C, which, despite its simplicity code-wise, it offers a straightforward and elegant interface for editing .ppm and .pgm image files, utilizing a low amount of hardware resources, which makes it a great choice for quick image adjustments.

---

## Who is this program for?

* Simps for CLI
* People with ~~`outdated`~~ budget technology
* Lab assistants

---

## Usage

Once the program is run, the user can execute different commands, listed below:

* LOAD \<$image\_ name$>
Loads an image into active memory. This is the first command that must be executed after starting the program.

* SELECT \<$x_1$> \<$y_1$> \<$x_2$> \<$y_2$>
Makes a rectangular selection of pixels, having the two given pixels as corners. The syntax for the SELECT command allows for $x_1$ and $x_2$ or $y_1$ and $y_2$ to be given in any order, but $x$'s and $y$'s cannot be interchanged.

* SELECT ALL
Selects the whole image.

* ROTATE \<$angle$>
Rotates the current selection clockwise. The $angle$ must be either 0, &#177; 90, &#177; 180, &#177; 270, &#177; 360. The selection must be a square or the whole image.
* CROP
Crops the image to the current selection.

* HISTOGRAM \<$x$> \<$y$>
Outputs the histogram of the image, with $y$ number of bins and at most $x$ number of data points. The image must be <span style="color:gray;font-weight:bold">grayscale</span> (.pgm).

* EQUALIZE
Equalizes the ratio of high-intensity pixels to low-intensity pixels, balancing the light level of the image. The image must be <span style="color:gray;font-weight:bold">grayscale</span> (.pgm).

* APPLY <$parameter$>
Applies a filter to the whole image. The filter can be EDGE, SHARPEN, BLUR or GAUSSIAN_BLUR. The image must be <span style="color:red;font-weight:bold">R</span><span style="color:green;font-weight:bold">G</span><span style="color:navy;font-weight:bold">B</span> (.ppm).

* SAVE <$file\_ name$> [$ascii$]
Saves the image, creating a new file or replacing the file, if it already exists. The optional parameter $ascii$ tells the program to save the image in plain format instead of binary.

* EXIT
Frees all allocated resources and exits the program. An image **MUST** have been loaded previously for the command to work.

---

## Implementation

* ### Interpreting commands

  The program interprets all commands **LINE BY LINE**. A command mustn't be spread out over multiple lines, nor more than one command be inputted on the same line. Either of the two will lead to errors.
<br>

* ### Storing images

    All images as stored as a structure, defined as follows:

    ```C
    typedef struct image {
    char type[2];
    unsigned long width, height;
    unsigned long x1, y1, x2, y2;
    void *color;
    } img;
    ```

  * $type$ stores the image's type, which can be either *P2*, *P3*, *P5* or *P6*.
  * $width$ stores the image's width, in pixels.
  * $height$ stores the image's height, in pixels.
  * $x_1$, $y_1$, $x_2$, and $y_2$ store the coordinates of the pixels that define the current selection.
  * $color$ is the address of the pixel array, or the image proper. For grayscale images, this array is of type <span style="color:aquamarine">unsigned char \*\*</span>, while for RGB images, the array is of type <span style="color:aquamarine">unsigned char\*\*\*</span>.
  This is done to optimize memory usage.
    * For grayscale images, all pixel values are stored as <span style="color:aquamarine">unsigned char</span>, in a $height\times width$ array (<span style="color:aquamarine">unsigned char</span> array\[height\]\[width\]).
    * For RGB images, all pixel values are stored as <span style="color:aquamarine">unsigned char[3]</span>, where the values of this vector are the values of the red, green, and blue intensity of the pixel, in this order. The pixels are stored in a $height\times width$ array (<span style="color:aquamarine">unsigned char</span> array\[height\]\[width\][3]).
<br>

* ### Allocating memory

  The program dynamically allocates memory for the pixel array, according to the image's type, width, and height, optimizing memory usage.
<br>

* ### Loading an image

  The image data is read from the input file using *fscanf* for the plain format, or *fread* for the binary format. Comments are skipped by first checking the first character of the line and, if it's '#', reading and discarding the whole line, all the way to the '\n' character.
<br>

* ### Selecting the whole image

  SELECT ALL will make the selection $"0\ 0\ width\ height"$, where $width$ and $height$ are the dimensions of the image.
<br>

* ### Equalizing an image

  The program determines the number of apparitions for all pixel intensities and stores them in a vector. Afterward, it calculates the new value for each pixel intensity, using the following formula:

  $$new\_ value= 255 * F_X(old\_ value)$$

  where $255$ is the highest possible value for a pixel and $F_X$ is the cumulative distribution function of the old value, described as follows:

  $$F_X(value)=\frac{\displaystyle\sum_{i=0}^{value}apparitions(i)}{total}\$$

  where $apparitions(i)$ is the number of apparitions of the value $i$ and $total$ is the total number of pixels of the image, calculated as $image\_ height\cdot image\_ width$.

  After the new values are calculated, each pixel in the image is given its corresponding value.
<br>

* ### Calculating the histogram

  The program determines the value of each bin by going through the pixel array and incrementing by one, for each pixel, its corresponding bin, determined by the formula:

  $$bin\_ nr = \frac{pixel\_ value}{range}$$

  where $range$ is the range of the bin, defined as:

  $$range = \frac{256}{y}$$

  where $256$ is the total number of pixel intensities and $y$ is the total number of bins, given as input.

  Afterward, the number of stars with which each bin will be represented is calculated with the following formula:

  $$nr\_ stars= \frac{value(bin)}{max\_ value}\ \cdot \ x$$

  where $value(bin)$ is the value of the bin, $max\_ value$ is the highest value of all the bins and $x$ is the maximum number of stars, given as input.
<br>

* ### Applying a filter

  Each filter has a corresponding image kernel, which is used to find the new values of the pixels. These kernels are:

  $$EDGE:
  \begin{bmatrix}
  -1 & -1 & -1\\
  -1 & 8 & -1\\
  -1 & -1 & -1
  \end{bmatrix}
  $$
  $$SHARPEN:
  \begin{bmatrix}
  0 & -1 & 0\\
  -1 & 5 & -1\\
  0 & -1 & 0
  \end{bmatrix}
  $$
  $$BLUR:\frac{1}{9}\ \cdot
  \begin{bmatrix}
  1 & 1 & 1\\
  1 & 1 & 1\\
  1 & 1 & 1
  \end{bmatrix}
  $$
  $$GAUSSIAN\_ BLUR:\frac{1}{16}\ \cdot
  \begin{bmatrix}
  1 & 2 & 1\\
  2 & 4 & 2\\
  1 & 2 & 1
  \end{bmatrix}
  $$

  These kernels are applied to every pixel of the selection, for each of its color channels, by the following rules:
  * The value of the pixel is multiplied by the center value of the image kernel;
  * The surrounding pixels are multiplied by their corresponding values in the image kernel.
  * All these values are summated and, if need be, divided by the image kernel's division constant (Ex: for BLUR, the sum is divided by 9). The resulting value is the new value of the pixel, which is stored in a temporary array.

  For more information on image kernels, please visit this *[site](https://setosa.io/ev/image-kernels/).*

  After all the values are calculated, they are copied from the temporary array to the pixel array.
<br>

* ### Cropping an image

  All pixels from the selection are swapped with the ones at the top left of the image (at the origin of the pixel array), then all the excess memory is freed and the pixel array is reallocated to its new size.
<br>

* ### Rotating an image with linear algebra

  Geometrically, we can imagine an array of pixels as an array of points on a two-dimensional plane, each point corresponding to a pixel, with the origin of the plane being the top-left corner point of the array. Visually, it would look like this:

  <p align="center">
    <img src="https://lh3.googleusercontent.com/Wg32He45RksetwLKMVSwJTmEEmTIbtQwuATDJV8mbO0WFZhscyGlA7oyWopMGpTNLYs=w2400">
  </p>

  The coordinates of these points would be the indices of the corresponding pixel in the pixel array. As such, we can represent these points with their position vectors, in the orthonormal basis $\left\{ \overline{i} = \begin{bmatrix}1\\ 0\end{bmatrix},\overline{j} = \begin{bmatrix} 0\\ -1\end{bmatrix}\right\}$, $\overline{i}$ being the unit vector for the $x$ axis and $\overline{j}$ being the unit vector for the $y$ axis. To put it simply, a point can be defined as a vector $\begin{bmatrix} x\\ y\end{bmatrix}$, where $x$ and $y$ are the coordinates of the point.

  To rotate this image, we can apply a linear transformation to every point of the array. For clockwise rotation, the linear transformation is:

  $$\begin{bmatrix}
  \cos \theta & \sin \theta \\
  -\sin \theta & \cos \theta
  \end{bmatrix}$$

  where $\theta$ is the rotation angle.

  $$\forall x,y\in\Z_+, \begin{bmatrix} \cos \theta & \sin \theta \\ -\sin \theta & \cos \theta \end{bmatrix}\cdot \begin{bmatrix} x\\ y\end{bmatrix} = \begin{bmatrix} \cos \theta\cdot x\ +\ \sin\theta \cdot y\\ -\sin\theta\cdot x\ +\ \cos\theta \cdot y\end{bmatrix}$$

  As such, to rotate the pixel array, we can build a temporary array, with its values defined by the formula:

  $$rotated\_ array\left[y\right]\left[x\right] = old\_ array\left[\cos \theta\cdot y\ -\ \sin\theta \cdot x\ +\ t_1\right]\left[\sin\theta\cdot y\ +\ \cos\theta \cdot x\ +\ t_2\right]$$
  $$y = \overline{0,h};\ x = \overline{0,w}$$

  where $h$ is the height of the selection and $w$ is the width of the selection.

  Depending on the angle of rotation, the indices of the selection will need to be adjusted. Whenever we have a negative number as an index, we need to add $y_2 - 1$, if it's the row index, or $x_2 - 1$, if it's the column index, in order to start from the end of the row/column, where $x_2$ and $y_2$ are the coordinated of the last pixel of the selection. Similarly, if the index is positive, we add $y_1$ or $x_1$, in order to start from the beginning of the row/column, where $x_1$ and $y_1$ are the coordinates of the first pixel of the selection.

  * $t_1$ is added to the row index. We know that, for any of the possible angles, either the sin or the cos will be 0, so their sum will be one or the other. If sin is positive or cos is negative, the index will have a negative sign, meaning that -sin and cos are negative and, since their sum is one or the other, their sum is negative. Secondly, if the index has a positive sign, it means that this sum must be positive. By checking the sign of this sum, we can determine whether to add $y_2 - 1$, if the sum is negative, or $y_1$, if it's positive.
  * $t_2$ is added to the column index. Similar logic to $t_1$ is applied.

  The values of the temporary array are copied into the original pixel array.

  For more information on rotation matrices, please visit this [*site*](https://en.wikipedia.org/wiki/Rotation_matrix).
<br>

* ### Saving an image

  The image data is written in the output file using *fprintf* for the plain format, or *write* for binary format. Not much to say.
