<?php 
    $con = mysqli_connect("localhost", "msm4585", "pigcoo1004!", "msm4585");
    mysqli_query($con,'SET NAMES utf8');
 
    $flag = $_POST["flag"];


    $statement = mysqli_prepare($con, "UPDATE Security SET flag=(?) where Locker_ID='1'");
    mysqli_stmt_bind_param($statement, "s", $flag);
    mysqli_stmt_execute($statement);
 
    $response = array();
    $response["success"] = true;
    $response["flag_data"] = $flag;
 
    echo json_encode($response);
?>