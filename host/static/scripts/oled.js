//=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=
//
//  >>  oled.js
//  >>  Created by Jack, Feb 17, 2018
//  >>  ...............
//
//=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=

function UnitTest() {
	let pitch, roll, yaw;
	$.getJSON('api/status', (json) => {
		console.log(json);
		for(let i in json) {
			if(json[i] == '0') {
				$(".screen").children().eq(i).css("background-color", "black");
			} else {
				$(".screen").children().eq(i).css("background-color", "red");

			}
		}
		// if (g__pitch < 0)
		// 	g__roll = -180 - g__roll;
	})

	// HUD.fresh(g__pitch, g__roll, g__yaw, motor1, motor2);
}

$(() => {
	for(let i = 0; i < 128*128; i++) {
		$(".screen").append('<div></div>');
	}
	setInterval(UnitTest, 100);
});