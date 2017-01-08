/*
 * GUIException.h
 *
 *  Created on: 7 ene. 2017
 *      Author: xmbeat
 */

#ifndef XMTOOLKIT_GUI_GUIEXCEPTION_H_
#define XMTOOLKIT_GUI_GUIEXCEPTION_H_

#include <exception/Exception.h>

namespace XmToolKit {

	class GUIException: public Exception {
		public:
			GUIException(String description);
			virtual ~GUIException();
	};

} /* namespace XmToolKit */

#endif /* XMTOOLKIT_GUI_GUIEXCEPTION_H_ */
