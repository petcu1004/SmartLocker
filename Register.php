<?php 
    $con = mysqli_connect("localhost", "msm4585", "pigcoo1004!", "msm4585");
    mysqli_query($con,'SET NAMES utf8');
 
    $Student_ID = $_POST["Student_ID"];
    $Student_PW = $_POST["Student_PW"];
    $Name = $_POST["Name"];
    $Phone = $_POST["Phone"];
    $Locker_ID = $_POST["Locker_ID"];
    $Locker_PW = $_POST["Locker_PW"];

 
    $statement = mysqli_prepare($con, "INSERT INTO User VALUES (?,?,?,?,?,?)");
    mysqli_stmt_bind_param($statement, "ssssss", $Student_ID, $Student_PW, $Name, $Phone, $Locker_ID, $Locker_PW);
    mysqli_stmt_execute($statement);
 
    $response = array();
    $response["success"] = true;
 
    echo json_encode($response);
?>