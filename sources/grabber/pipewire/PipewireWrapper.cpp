/* PipewireWrapper.cpp
*
*  MIT License
*
*  Copyright (c) 2023 awawa-dev
*
*  Project homesite: https://github.com/awawa-dev/HyperHDR
*
*  Permission is hereby granted, free of charge, to any person obtaining a copy
*  of this software and associated documentation files (the "Software"), to deal
*  in the Software without restriction, including without limitation the rights
*  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
*  copies of the Software, and to permit persons to whom the Software is
*  furnished to do so, subject to the following conditions:
*
*  The above copyright notice and this permission notice shall be included in all
*  copies or substantial portions of the Software.

*  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
*  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
*  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
*  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
*  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
*  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
*  SOFTWARE.
 */

#include <QMetaType>
#include <grabber/PipewireWrapper.h>


PipewireWrapper::PipewireWrapper(const QString &device,
		const QString & configurationPath )
	: SystemWrapper("PIPEWIRE_SYSTEM:"+device.left(14), &_grabber)
	, _grabber(device, configurationPath)
{	
	qRegisterMetaType<Image<ColorRgb>>("Image<ColorRgb>");
	connect(&_grabber, &Grabber::newFrame, this, &SystemWrapper::newFrame, Qt::DirectConnection);
	connect(&_grabber, &Grabber::readError, this, &SystemWrapper::readError, Qt::DirectConnection);
}

QString PipewireWrapper::getGrabberInfo()
{
	return "pipewire";
}

bool PipewireWrapper::isActivated(bool forced)
{
	return _grabber.hasPipewire(forced);
}

void PipewireWrapper::stateChanged(bool state)
{
	_grabber.stateChanged(state);
}

void PipewireWrapper::processFrame(const PipewireImage& frame)
{
	_grabber.grabFrame(frame);
}

