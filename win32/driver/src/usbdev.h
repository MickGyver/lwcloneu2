/*
 * LWCloneU2
 * Copyright (C) 2013 Andreas Dittrich <lwcloneu2@cithraidt.de>
 *
 * This program is free software; you can redistribute it and/or modify it under the terms of the
 * GNU General Public License as published by the Free Software Foundation;
 * either version 2 of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along with this program;
 * if not, write to the Free Software Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#ifndef USBDEV_H__INCLUDED
#define USBDEV_H__INCLUDED


typedef void * HUDEV;

HUDEV usbdev_create(LPCSTR devicepath);
void usbdev_addref(HUDEV hudev);
void usbdev_release(HUDEV hudev);
size_t usbdev_read(HUDEV hudev, void *pdata, size_t ndata);
void usbdev_clear_input(HUDEV hudev, size_t input_report_len);
size_t usbdev_write(HUDEV hudev, void const *pdata, size_t ndata);
HANDLE usbdev_handle(HUDEV hudev);
void usbdev_set_min_write_interval(HUDEV hudev, unsigned int interval_ms);



#endif
