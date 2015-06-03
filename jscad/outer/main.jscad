include("common.jscad");

function outer_objects() {
    var tolerance = 1;
    var outer_margin = margin + tolerance;
	var outer_base = translate(
				[-outer_margin, -outer_margin, 0], 
				base_plate_2D(inner_radius+outer_margin)); 
	var outer_height = inner_height + base_thickness;

	var edge = 
        difference( 
			linear_extrude({height: outer_height + 20}, outer_base), 
             translate(
    			[-tolerance, -tolerance, 0],
			    linear_extrude({height: outer_height + margin}, base_plate_2D(inner_radius + tolerance))
             )
		);

	var objects = [];
	for(var min_or_max = 0; min_or_max<=1; min_or_max++) {
		var socket = screw_socket(min_or_max);
		var socket_offset = edge.getBounds()[min_or_max].y - socket.getBounds()[min_or_max].y;
	
		objects.push(
			difference(
				union(socket, 
					translate(
						[0, socket_offset, 0],
						screw_socket(min_or_max)
					)),
				screw_socket_hole(min_or_max)
			));
	}
    
	objects.push(difference(
        edge,        
        translate([0, 0, outer_height + 20],
            rotate([0, 30, 0],
                translate([-inner_radius, -outer_margin, 0],
                    cube( {size: [
                        4*inner_radius,
                        inner_length+2*inner_radius + 2*outer_margin,
                        30]}
                    ))))));
                    
	return objects;
}

function main() {
	return outer_objects();
}