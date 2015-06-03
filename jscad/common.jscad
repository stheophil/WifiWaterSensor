base_thickness = 2;

charger_hole_dim = [8, 4, base_thickness];
var screw_radius = 1.5;
var screw_length = 8;

battery_dim = [22, 21, 78];
charger_dim = [17, 1, 26];
wifi_dim = [26, 1, 50]; // NodeMCU esp8266, and adafruit huzzah

margin = 2;
inner_length = 40;

var inner_width = Math.max(
    battery_dim[0], charger_dim[0], wifi_dim[0]
) + margin; // incl 1mm tolerance on each side

inner_height = Math.max(
    battery_dim[2],
    charger_dim[2] + wifi_dim[2] + 2
);

inner_radius = inner_width/2;
vertical_slab_dim = [inner_width - margin, 2, inner_height];

base_plate_2D = function base_plate_2D(radius) {
	return hull( 
			circle({r: radius}), 
			translate( 
			[0, inner_length, 0], 
			circle({r: radius})));
}

base_plate = function base_plate(radius) {
	return linear_extrude( 
		{height: base_thickness},
		base_plate_2D(radius));
}

object = function object(dim, yoffset, zoffset) {
	if(arguments.length<3) zoffset = base_thickness;

	return translate(
			[(inner_width-dim[0])/2, yoffset, zoffset],
			cube({size: dim}));
}

helper_object = function helper_object(dim, yoffset, zoffset) {
	if(arguments.length<3) zoffset = base_thickness;
	return color([0.8, 0.8, 0.8], object(dim, yoffset, zoffset));
}

function screw_center(min_or_max) {
	var base = base_plate(inner_radius); 
	var offset = margin + screw_radius;
	if(min_or_max == 1) offset *= -1;

	return [inner_width/2, 
		base.getBounds()[min_or_max].y + offset,
		0];
}

screw_hole = function screw_hole(min_or_max) {
	return translate(
		screw_center(min_or_max),
		cylinder({r: screw_radius, h: base_thickness}));
}

function internal_screw_socket(min_or_max, radius) {
	var center = screw_center(min_or_max);
	center[2] = base_thickness;

	return translate(
		center,
		cylinder({r: radius, h: screw_length}));
}

screw_socket = function screw_socket(min_or_max) {
	return internal_screw_socket(min_or_max, 2*screw_radius);
}

screw_socket_hole = function screw_socket_hole(min_or_max) {
	return internal_screw_socket(min_or_max, screw_radius);
}