Post

# Post

## Arguments

- url
	- Type: String
	-  A string containing the URL to which the request is sent
-  data
	-  Type: PlainObject or String
	-  A plain object or string that is sent to the server with the request
-  success
	-  Type: Function(PlainObject data, String textStatus, jqXHR jqXHR)
	-  A callback function that is executed if the request succeeds. Required if dataType is provided, but can be null in that case
-  dataType
	-  Type: String
	-  The type of data expected from the server. Default: intelligent Guess(xml, json, text, html)


## Syntax

`$.ajax({
	type: "POST",
	url: url,
	data: {
			arg1: "arg1",
			arg2: "arg2",
	},
	success: function(result){
		alert("HELLO");
	},
	dataType: dataType
	});`