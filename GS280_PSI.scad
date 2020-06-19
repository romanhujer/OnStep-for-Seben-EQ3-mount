/* Astro caps
             0

   Copyright (c) 2020 Roman Hujer   http://hujer.net

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,ss
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.

  Description: 

*/

use <threads.scad>

// 1 Edge HD 3.25" Cap  (Optec Lepus  0.62x  or T2) 
// 2 SCT  2"     Cap 
// 3 M48 x 0.75  Cap
// 4 M42 x 0.75  Cap



  difference() {
    union()  {
       translate([0,0,-10])english_thread (diameter=0.4, threads_per_inch=16, length=1.1);
       cylinder (h = 20, r=3, center = true, $fn=100 );
       translate([0,0,20])cylinder (h = 10, r=8, center = true, $fn=100 );
   }
    
        translate([0,0,10])cylinder (h = 50, r=2, center = true, $fn=100 );
   
   
   
 }

    