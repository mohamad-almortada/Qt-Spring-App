package com.example.employee.modell;

import com.fasterxml.jackson.annotation.JsonProperty;

import javax.persistence.*;
import java.time.LocalDate;


@Entity
@Table(name = "EMPLOYEES")
public class Employee {


    public Employee(@JsonProperty("firstname") String firstname,
                    @JsonProperty("lastname") String lastname,
                    @JsonProperty("age") int age,
                    @JsonProperty("salary") double salary,
                    @JsonProperty("birth") LocalDate birth,
                    @JsonProperty("entrance") LocalDate entrance,
                    @JsonProperty("gender") String gender,
                    @JsonProperty("tel") String tel){
        this.firstname = firstname;
        this.lastname = lastname;
        this.age = age;
        this.salary = salary;
        this.birth = birth;
        this.entrance = entrance;
        this.gender = gender;
        this.tel =tel;
    }

    public Employee() {
    }



    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    private long id;


    @Column(name = "firstname")
    private String firstname;

    @Column(name = "lastname")
    private String lastname;

    @Column(name = "age",nullable = false)
    private int age;

    @Column(name = "salary")
    private double salary;

    @Column(name = "birth")
    private LocalDate birth;

    @Column(name = "entrance")
    private LocalDate entrance;

    @Column(name = "gender")
    private String gender;

    @Column(name = "tel")
    private String tel;

    public String getTel(){return  tel;}

    public void setTel(String tel){this.tel = tel;}

    public long getId() {
        return id;
    }

    public void setId(long id) {
        this.id = id;
    }

    public String getFirstname() {
        return firstname;
    }

    public void setFirstname(String firstname) {
        this.firstname = firstname;
    }

    public String getLastname() {
        return lastname;
    }

    public void setLastname(String lastname) {
        this.lastname = lastname;
    }


    public int getAge() {
        return age;
    }

    public void setAge(int age) {
        this.age = age;
    }

    public double getSalary() {
        return salary;
    }

    public void setSalary(double salary) {
        this.salary = salary;
    }

    public LocalDate getBirth() {
        return birth;
    }

    public void setBirth(LocalDate birth) {
        this.birth = birth;
    }

    public LocalDate getEntrance() {
        return entrance;
    }

    public void setEntrance(LocalDate entrance) {
        this.entrance = entrance;
    }

    public String getGender() {
        return gender;
    }

    public void setGender(String gender) {
        this.gender = gender;
    }
}
