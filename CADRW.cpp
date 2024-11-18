#include "CADRW.h"

CADRW::CADRW(dxfRW &dxfw) :m_dxfW(dxfw) {
}

void CADRW::dxfWrite(dxfRW & dxfW)
{
	DRW_Line line;
	line.basePoint.x = 100;
	line.basePoint.y = 200;
	line.secPoint.x = 300;
	line.secPoint.y = 300;
	dxfW.writeLine(&line);

	DRW_Line line2;
	line2.basePoint.x = 0;
	line2.basePoint.y = 0;
	line2.secPoint.x = 0;
	line2.secPoint.y = 300;
	dxfW.writeLine(&line2);
}


