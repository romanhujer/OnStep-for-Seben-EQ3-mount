difference()
{
 union(){   
  cylinder(h=0.5, r=17, center=true, $fn=360);
  translate ([16.7,0,0])cylinder(h=0.5, r=3, center=true, $fn=360);
  rotate([0,0,120])translate ([16.7,0,0])cylinder(h=0.5, r=3, center=true, $fn=360);
  rotate([0,0,-120])translate ([16.7,0,0])cylinder(h=0.5, r=3, center=true, $fn=360);
     
 
 }
 
 union(){       

 cylinder(h=0.5, r=28/2, center=true, $fn=360);
  translate ([16.7,0,0])cylinder(h=0.5, r=1.1, center=true, $fn=360);
  rotate([0,0,120])translate ([16.7,0,0])cylinder(h=0.5, r=1.1, center=true, $fn=360);
  rotate([0,0,-120])translate ([16.7,0,0])cylinder(h=0.5, r=1.1, center=true, $fn=360);
  rotate([0,0,-67.5]) translate ([16.3,-10,-1])cube([4,20,2]);

 }
    }
    
    
    
/*    
difference()
{
    
 cylinder(h=7, r=6, center=true, $fn=360);

 cylinder(h=7, r=2.8, center=true, $fn=360);

    
    }    
    
    */
    