<?php 
    $con = mysqli_connect("localhost", "msm4585", "pigcoo1004!", "msm4585");
    mysqli_query($con,'SET NAMES utf8');
 
    $Locker_ID = $_POST["Locker_ID"];


    $statement = mysqli_prepare($con, "UPDATE Locker SET Using_check='1' where Locker_ID=(?)");
    mysqli_stmt_bind_param($statement, "s", $Locker_ID);
    mysqli_stmt_execute($statement);
 
    $response = array();
    $response["success"] = true;
 
    echo json_encode($response);
?>