<?php
    $con = mysqli_connect("localhost", "msm4585", "pigcoo1004!", "msm4585");
    mysqli_query($con,'SET NAMES utf8');
 
    $Student_ID = $_POST["Student_ID"];
    $Student_PW = $_POST["Student_PW"];
    
    $statement = mysqli_prepare($con, "SELECT * FROM User WHERE Student_ID = ? AND Student_PW = ?");
    mysqli_stmt_bind_param($statement, "ss", $Student_ID, $Student_PW);
    mysqli_stmt_execute($statement);
 
 
    mysqli_stmt_store_result($statement);
    mysqli_stmt_bind_result($statement, $Student_ID, $Student_PW, $Name, $Phone, $Locker_ID, $Locker_PW);
 
    $response = array();
    $response["success"] = true;
 
    while(mysqli_stmt_fetch($statement)) {
        $response["success"] = true;
        $response["Student_ID"] = $Student_ID;
        $response["Student_PW"] = $Student_PW;
    }
 
    echo json_encode($response);
?>