<?php
    $con = mysqli_connect("localhost", "msm4585", "pigcoo1004!", "msm4585");
    mysqli_query($con,'SET NAMES utf8');
 

    $Locker_PW = $_POST["Locker_PW"];
    
    $statement = mysqli_prepare($con, "SELECT * FROM User WHERE Locker_ID = '1' AND Locker_PW = ?");
    mysqli_stmt_bind_param($statement, "s", $Locker_PW);
    mysqli_stmt_execute($statement);
 
 
    mysqli_stmt_store_result($statement);
    mysqli_stmt_bind_result($statement, $Student_ID, $Student_PW, $Name, $Phone, $Locker_ID, $Locker_PW);
 
    $response = array();
    $response["success"] = true;
 
    while(mysqli_stmt_fetch($statement)) {
        $response["success"] = true;
        $response["Locker_PW"] = $Locker_PW;
    }
 
    echo json_encode($response);
?>