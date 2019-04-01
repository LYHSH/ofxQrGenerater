/*
* QR Code generator library (C++)
*
* Copyright (c) Project Nayuki. (MIT License)
* https://www.nayuki.io/page/qr-code-generator-library
*
* Permission is hereby granted, free of charge, to any person obtaining a copy of
* this software and associated documentation files (the "Software"), to deal in
* the Software without restriction, including without limitation the rights to
* use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
* the Software, and to permit persons to whom the Software is furnished to do so,
* subject to the following conditions:
* - The above copyright notice and this permission notice shall be included in
*   all copies or substantial portions of the Software.
* - The Software is provided "as is", without warranty of any kind, express or
*   implied, including but not limited to the warranties of merchantability,
*   fitness for a particular purpose and noninfringement. In no event shall the
*   authors or copyright holders be liable for any claim, damages or other
*   liability, whether in an action of contract, tort or otherwise, arising from,
*   out of or in connection with the Software or the use or other dealings in the
*   Software.
*/
#include "ofxQrGenerater.h"
#include "QrCode.hpp"
using namespace qrcodegen;


ofxQrGenerater::ofxQrGenerater()
{
}


ofxQrGenerater::~ofxQrGenerater()
{
}

ofPixels ofxQrGenerater::generate(string _text,int _size)
{
	QrCode qr = QrCode::encodeText(_text.c_str(), QrCode::Ecc::HIGH);
	ofLogNotice("ofxQrGenerater") <<"QR SIZE:"<< qr.getSize() << endl;
	ofLogNotice("ofxQrGenerater") <<"QR VERSION:"<< qr.getVersion() << endl;

	int qrSize = qr.getSize();

	int gridsize = _size / qrSize;

	if (gridsize <= 0)gridsize = 1;

	ofLogNotice("ofxQrGenerater") << "ZOOM SCALE:" << gridsize << endl;

	ofPixels pixel;
	pixel.allocate(qrSize * gridsize, qrSize * gridsize, OF_IMAGE_COLOR);

	for (int y = 0; y < qrSize; y++) {
		for (int x = 0; x < qrSize; x++) {
			int value = qr.getModule(x, y) ? 0 : 255;
			for (int ver = 0; ver < gridsize; ver++)
			{
				for (int hor = 0; hor < gridsize; hor++)
				{
					pixel.setColor(x * gridsize + hor, y * gridsize + ver, ofColor(value));
				}
			}
		}
	}

	return pixel;
}
