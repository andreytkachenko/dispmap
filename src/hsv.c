/*#include <opencv2/opencv.hpp>

CvScalar HSVtoRGBcvScalar(int H, int S, int V) {

	int bH = H; // H component
	int bS = S; // S component
	int bV = V; // V component
	float fH, fS, fV;
	float fR, fG, fB;
	const float FLOAT_TO_BYTE = 255.0f;
	const float BYTE_TO_FLOAT = 1.0f / FLOAT_TO_BYTE;

// Convert from 8-bit integers to floats
	fH = (float) bH * BYTE_TO_FLOAT;
	fS = (float) bS * BYTE_TO_FLOAT;
	fV = (float) bV * BYTE_TO_FLOAT;

// Convert from HSV to RGB, using float ranges 0.0 to 1.0
	int iI;
	float fI, fF, p, q, t;

	if (bS == 0) {
// achromatic (grey)
		fR = fG = fB = fV;
	} else {
// If Hue == 1.0, then wrap it around the circle to 0.0
		if (fH >= 1.0f)
		fH = 0.0f;

		fH *= 6.0; // sector 0 to 5
		fI = floor(fH); // integer part of h (0,1,2,3,4,5 or 6)
		iI = (int) fH; // " " " "
		fF = fH - fI; // factorial part of h (0 to 1)

		p = fV * (1.0f - fS);
		q = fV * (1.0f - fS * fF);
		t = fV * (1.0f - fS * (1.0f - fF));

		switch (iI) {
		case 0:
			fR = fV;
			fG = t;
			fB = p;
			break;
		case 1:
			fR = q;
			fG = fV;
			fB = p;
			break;
		case 2:
			fR = p;
			fG = fV;
			fB = t;
			break;
		case 3:
			fR = p;
			fG = q;
			fB = fV;
			break;
		case 4:
			fR = t;
			fG = p;
			fB = fV;
			break;
		default: // case 5 (or 6):
			fR = fV;
			fG = p;
			fB = q;
			break;
		}
	}

// Convert from floats to 8-bit integers
	int bR = (int) (fR * FLOAT_TO_BYTE);
	int bG = (int) (fG * FLOAT_TO_BYTE);
	int bB = (int) (fB * FLOAT_TO_BYTE);

// Clip the values to make sure it fits within the 8bits.
	if (bR > 255)
	bR = 255;
	if (bR < 0)
	bR = 0;
	if (bG > 255)
	bG = 255;
	if (bG < 0)
	bG = 0;
	if (bB > 255)
	bB = 255;
	if (bB < 0)
	bB = 0;

// Set the RGB cvScalar with G B R, you can use this values as you want too..
	return cvScalar(bB, bG, bR); // R component
}*/
