package com.example.employee.modell;

import javax.persistence.Column;
import java.util.Date;
import org.modelmapper.*;


public class EmployeeDto {

    private String firstname;
    private String lastname;
    private int age;
    private double salary;
    private Date birth;
    private Date entrance;
    private String gender;
}
