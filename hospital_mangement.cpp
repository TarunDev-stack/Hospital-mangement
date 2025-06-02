#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <algorithm>
using namespace std;

class Patient {
private:
    int id;
    string name;
    int age;
    string gender;
    string contact;

public:
    Patient(int id, const string& name, int age, const string& gender, const string& contact)
        : id(id), name(name), age(age), gender(gender), contact(contact) {}

    int getId() const { return id; }
    string getName() const { return name; }
    int getAge() const { return age; }
    string getGender() const { return gender; }
    string getContact() const { return contact; }

    void display() const {
        cout << left << setw(6) << id << setw(20) << name << setw(6) << age
             << setw(10) << gender << setw(15) << contact << endl;
    }
};

class Doctor {
private:
    int id;
    string name;
    string specialty;
    string contact;

public:
    Doctor(int id, const string& name, const string& specialty, const string& contact)
        : id(id), name(name), specialty(specialty), contact(contact) {}

    int getId() const { return id; }
    string getName() const { return name; }
    string getSpecialty() const { return specialty; }
    string getContact() const { return contact; }

    void display() const {
        cout << left << setw(6) << id << setw(20) << name << setw(20) << specialty
             << setw(15) << contact << endl;
    }
};

class Appointment {
private:
    int appointmentId;
    int patientId;
    int doctorId;
    string date;
    string time;

public:
    Appointment(int appointmentId, int patientId, int doctorId, const string& date, const string& time)
        : appointmentId(appointmentId), patientId(patientId), doctorId(doctorId), date(date), time(time) {}

    int getAppointmentId() const { return appointmentId; }
    int getPatientId() const { return patientId; }
    int getDoctorId() const { return doctorId; }
    string getDate() const { return date; }
    string getTime() const { return time; }

    void display(const vector<Patient>& patients, const vector<Doctor>& doctors) const {
        const Patient* pPatient = nullptr;
        const Doctor* pDoctor = nullptr;

        for (const auto& p : patients) {
            if (p.getId() == patientId) {
                pPatient = &p;
                break;
            }
        }
        for (const auto& d : doctors) {
            if (d.getId() == doctorId) {
                pDoctor = &d;
                break;
            }
        }

        cout << left << setw(5) << appointmentId;
        if (pPatient)
            cout << setw(20) << pPatient->getName();
        else
            cout << setw(20) << "Unknown";

        if (pDoctor)
            cout << setw(20) << pDoctor->getName();
        else
            cout << setw(20) << "Unknown";

        cout << setw(12) << date << setw(8) << time << endl;
    }
};

class HospitalManagementSystem {
private:
    vector<Patient> patients;
    vector<Doctor> doctors;
    vector<Appointment> appointments;

    int patientIdCounter = 1;
    int doctorIdCounter = 1;
    int appointmentIdCounter = 1;

public:
    void addPatient() {
        string name, gender, contact;
        int age;
        cout << "Enter Patient Name: ";
        getline(cin, name);
        cout << "Enter Age: ";
        cin >> age;
        cin.ignore();
        cout << "Enter Gender: ";
        getline(cin, gender);
        cout << "Enter Contact Number: ";
        getline(cin, contact);

        patients.emplace_back(patientIdCounter++, name, age, gender, contact);
        cout << "Patient added successfully with ID: " << patientIdCounter - 1 << "\n\n";
    }

    void addDoctor() {
        string name, specialty, contact;
        cout << "Enter Doctor Name: ";
        getline(cin, name);
        cout << "Enter Specialty: ";
        getline(cin, specialty);
        cout << "Enter Contact Number: ";
        getline(cin, contact);

        doctors.emplace_back(doctorIdCounter++, name, specialty, contact);
        cout << "Doctor added successfully with ID: " << doctorIdCounter - 1 << "\n\n";
    }

    void scheduleAppointment() {
        if (patients.empty()) {
            cout << "No patients available. Please add patients first.\n\n";
            return;
        }
        if (doctors.empty()) {
            cout << "No doctors available. Please add doctors first.\n\n";
            return;
        }

        int pId, dId;
        string date, time;

        cout << "Enter Patient ID: ";
        cin >> pId;
        cin.ignore();
        if (!patientExists(pId)) {
            cout << "Patient ID not found.\n\n";
            return;
        }

        cout << "Enter Doctor ID: ";
        cin >> dId;
        cin.ignore();
        if (!doctorExists(dId)) {
            cout << "Doctor ID not found.\n\n";
            return;
        }

        cout << "Enter Appointment Date (YYYY-MM-DD): ";
        getline(cin, date);
        cout << "Enter Appointment Time (HH:MM): ";
        getline(cin, time);

        appointments.emplace_back(appointmentIdCounter++, pId, dId, date, time);
        cout << "Appointment scheduled successfully with Appointment ID: " << appointmentIdCounter - 1 << "\n\n";
    }

    void showAllPatients() const {
        if (patients.empty()) {
            cout << "No patients available.\n\n";
            return;
        }
        cout << left << setw(6) << "ID" << setw(20) << "Name" << setw(6) << "Age" << setw(10) << "Gender"
             << setw(15) << "Contact" << "\n";
        cout << "---------------------------------------------------------------\n";
        for (const auto& p : patients) {
            p.display();
        }
        cout << "\n";
    }

    void showAllDoctors() const {
        if (doctors.empty()) {
            cout << "No doctors available.\n\n";
            return;
        }
        cout << left << setw(6) << "ID" << setw(20) << "Name" << setw(20) << "Specialty"
             << setw(15) << "Contact" << "\n";
        cout << "---------------------------------------------------------------\n";
        for (const auto& d : doctors) {
            d.display();
        }
        cout << "\n";
    }

    void showAllAppointments() const {
        if (appointments.empty()) {
            cout << "No appointments scheduled.\n\n";
            return;
        }
        cout << left << setw(5) << "AppID" << setw(20) << "Patient" << setw(20) << "Doctor"
             << setw(12) << "Date" << setw(8) << "Time" << "\n";
        cout << "---------------------------------------------------------------\n";
        for (const auto& a : appointments) {
            a.display(patients, doctors);
        }
        cout << "\n";
    }

    void searchPatient() const {
        int id;
        cout << "Enter Patient ID to search: ";
        cin >> id;
        cin.ignore();
        auto it = find_if(patients.begin(), patients.end(), [id](const Patient& p) { return p.getId() == id; });
        if (it != patients.end()) {
            cout << "Patient Details:\n";
            cout << left << setw(6) << "ID" << setw(20) << "Name" << setw(6) << "Age" << setw(10) << "Gender"
                 << setw(15) << "Contact" << "\n";
            cout << "---------------------------------------------------------------\n";
            it->display();
            cout << "\n";
        }
        else {
            cout << "Patient not found.\n\n";
        }
    }

    void searchDoctor() const {
        int id;
        cout << "Enter Doctor ID to search: ";
        cin >> id;
        cin.ignore();
        auto it = find_if(doctors.begin(), doctors.end(), [id](const Doctor& d) { return d.getId() == id; });
        if (it != doctors.end()) {
            cout << "Doctor Details:\n";
            cout << left << setw(6) << "ID" << setw(20) << "Name" << setw(20) << "Specialty"
                 << setw(15) << "Contact" << "\n";
            cout << "---------------------------------------------------------------\n";
            it->display();
            cout << "\n";
        }
        else {
            cout << "Doctor not found.\n\n";
        }
    }

private:
    bool patientExists(int id) const {
        return any_of(patients.begin(), patients.end(), [id](const Patient& p) { return p.getId() == id; });
    }
    bool doctorExists(int id) const {
        return any_of(doctors.begin(), doctors.end(), [id](const Doctor& d) { return d.getId() == id; });
    }
};

void showMenu() {
    cout << "======== Hospital Management System ========\n"
         << "1. Add Patient\n"
         << "2. Add Doctor\n"
         << "3. Schedule Appointment\n"
         << "4. Show All Patients\n"
         << "5. Show All Doctors\n"
         << "6. Show All Appointments\n"
         << "7. Search Patient by ID\n"
         << "8. Search Doctor by ID\n"
         << "9. Exit\n"
         << "Enter your choice: ";
}

int main() {
    HospitalManagementSystem hms;
    while (true) {
        showMenu();
        int choice;
        cin >> choice;
        cin.ignore(); // consume newline after number input

        switch (choice) {
            case 1:
                hms.addPatient();
                break;
            case 2:
                hms.addDoctor();
                break;
            case 3:
                hms.scheduleAppointment();
                break;
            case 4:
                hms.showAllPatients();
                break;
            case 5:
                hms.showAllDoctors();
                break;
            case 6:
                hms.showAllAppointments();
                break;
            case 7:
                hms.searchPatient();
                break;
            case 8:
                hms.searchDoctor();
                break;
            case 9:
                cout << "Exiting Program. Goodbye!\n";
                return 0;
            default:
                cout << "Invalid choice, please try again.\n\n";
                break;
        }
    }
    return 0;
}

