#include <iostream>
#include <vector>
#include <string>
#include <cctype> 
#include <algorithm> // for std::transform

class Doctor {
public:
    std::string name;
    std::string specialty;
    std::string shift; // "morning" or "night"
    std::vector<std::string> unavailableDays;

    Doctor(const std::string& n, const std::string& s, const std::string& sh, const std::vector<std::string>& unav) : name(n), specialty(s), shift(sh), unavailableDays(unav) {}
};

class Patient {
public:
    std::string name;
    int age;
    std::string gender;
    bool admitted;
    int wardNumber; // Assuming each patient is assigned a ward number

    Patient(const std::string& n, int a, const std::string& g) : name(n), age(a), gender(g), admitted(false) {}
};

class Ward {
public:
    int total;
    int reserved;

    Ward(int t) : total(t), reserved(0) {}

    // Function to update reserved wards when a patient is assigned
    void assignPatient() {
        reserved++;
    }

    // Function to update reserved wards when a patient is discharged
    void dischargePatient() {
        if (reserved > 0) {
            reserved--;
        }
    }

    // Function to get the number of free wards
    int getFreeWards() const {
        return total - reserved;
    }
};

class Appointment {
public:
    Patient patient;
    Doctor doctor;
    std::string date;

    Appointment(const Patient& p, const Doctor& d, const std::string& dt) : patient(p), doctor(d), date(dt) {}
};

class Hospital {
public:
    std::vector<Doctor> doctors;
    std::vector<Patient> patients;
    std::vector<Appointment> appointments;
    std::vector<Ward> wards;

    Hospital() {
        // Initialize wards
        wards.push_back(Ward(10)); // Example: 10 total wards
    }
    void registerDoctor(const Doctor& doctor) {
        doctors.push_back(doctor);
    }

    void registerPatient(const Patient& patient) {
        patients.push_back(patient);
    }

    void scheduleAppointment(const Patient& patient, const Doctor& doctor, const std::string& date) {
        Appointment appointment(patient, doctor, date);
        appointments.push_back(appointment);
    }

    void displayAppointments() const {
        std::cout << "Appointments:\n";
        for (std::vector<Appointment>::const_iterator it = appointments.begin(); it != appointments.end(); ++it) {
            const Appointment& appointment = *it;
            std::cout << "Date: " << appointment.date << "\n";
            std::cout << "Patient: " << appointment.patient.name << "\n";
            std::cout << "Doctor: " << appointment.doctor.name << " (Specialty: " << appointment.doctor.specialty << ")\n";
            std::cout << "------------------------\n";
        }
    }

    int countAvailableWards() const {
        int totalWards = 0;
        int reservedWards = 0;

        for (std::vector<Ward>::const_iterator it = wards.begin(); it != wards.end(); ++it) {
            totalWards += it->total;
            reservedWards += it->reserved;
        }

        return totalWards - reservedWards;
    }
    void assignWardToPatient(Patient& patient) {
    // Check if the patient is already admitted
    if (patient.admitted) {
        std::cout << "Patient " << patient.name << " is already admitted to Ward " << patient.wardNumber << ".\n";
        return;
    }

    // Find an available ward
    for (std::vector<Ward>::const_iterator it = wards.begin(); it != wards.end(); ++it) {
        if (it->reserved < it->total) {
            // Assign the ward to the patient
            const_cast<Ward&>(*it).assignPatient();
            patient.admitted = true;
            patient.wardNumber = it->reserved;
            std::cout << "Patient " << patient.name << " assigned to Ward " << patient.wardNumber << ".\n";
            return;
        }
    
   else{
    std::cout << "No available wards. Cannot admit patient.\n";
}
}
}

// Helper function for case-insensitive string comparison
bool caseInsensitiveCharCompare(char c1, char c2) {
    return std::tolower(c1) == std::tolower(c2);
}


void dischargePatientFromWard(Patient& patient) {
     
        if (patient.admitted && patient.wardNumber > 0) {
            // Find the ward and discharge the patient
            for (std::vector<Ward>::iterator it = wards.begin(); it != wards.end(); ++it) {
                if (it->reserved > 0) {
                    it->dischargePatient();
                    patient.admitted = false;
                    std::cout << "Patient " << patient.name << " discharged from Ward " << patient.wardNumber << ".\n";
                    patient.wardNumber = 0; // Reset the ward number
                    return;
                }
            }
        } else {
            std::cout << "Patient " << patient.name << " is not admitted to any ward.\n";
        }
    }


    void displayAvailableDoctors(const std::string& shift, const std::string& day) const {
        std::cout << "Available Doctors:\n";
        for (std::vector<Doctor>::const_iterator it = doctors.begin(); it != doctors.end(); ++it) {
            const Doctor& doctor = *it;
            if (doctor.shift == shift && std::find(doctor.unavailableDays.begin(), doctor.unavailableDays.end(), day) == doctor.unavailableDays.end()) {
                std::cout << "Doctor: " << doctor.name << " (Specialty: " << doctor.specialty << ")\n";
            }
        }
    }

    void prescribeMedicine(const Patient& patient, const std::string& medicine) {
        std::cout << "Prescribing " << medicine << " to patient " << patient.name << ".\n";
    }
    
    // Function to get the number of total, reserved, and free wards
    void getWardInfo() const {
        for (std::vector<Ward>::const_iterator it = wards.begin(); it != wards.end(); ++it) {
            std::cout << "Total Wards: " << it->total << "\n";
            std::cout << "Reserved Wards: " << it->reserved << "\n";
            std::cout << "Free Wards: " << it->getFreeWards() << "\n";
        }
    }
};

int main() {
    Hospital hospital;

    int choice;

    do {
        std::cout << "\nHospital Management System\n";
        std::cout << "1. Register Doctor\n";
        std::cout << "2. Register Patient\n";
        std::cout << "3. Schedule Appointment\n";
        std::cout << "4. View Appointments\n";
        std::cout << "5. Number of Wards\n";
        std::cout << "6. Available Doctors\n";
        std::cout << "7. Prescribe Medicine\n";
        std::cout << "8. Admit Patient & Assign Ward to Patient\n";
        std::cout << "9. Discharge Patient & Discharge Patient from Ward\n";
        std::cout << "0. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1: {
                std::string name, specialty, shift;
                std::vector<std::string> unavailableDays;

                std::cout << "Enter Doctor's Name: ";
                std::cin >> name;
                std::cout << "Enter Doctor's Specialty: ";
                std::cin >> specialty;
                std::cout << "Enter Doctor's Shift (morning/night): ";
                std::cin >> shift;

                int dayCount;
                std::cout << "Enter the number of days the doctor is unavailable: ";
                std::cin >> dayCount;

                std::cout << "Enter the unavailable days (e.g., Monday Tuesday): ";
                for (int i = 0; i < dayCount; ++i) {
                    std::string day;
                    std::cin >> day;
                    unavailableDays.push_back(day);
                }

                Doctor doctor(name, specialty, shift, unavailableDays);
                hospital.registerDoctor(doctor);
                std::cout << "Doctor registered successfully!\n";
                break;
            }
            case 2: {
                std::string name, gender;
                int age;
                std::cout << "Enter Patient's Name: ";
                std::cin >> name;
                std::cout << "Enter Patient's Age: ";
                std::cin >> age;
                std::cout << "Enter Patient's Gender: ";
                std::cin >> gender;
                Patient patient(name, age, gender);
                hospital.registerPatient(patient);
                std::cout << "Patient registered successfully!\n";
                break;
            }
            case 3: {
                std::string patientName, doctorName, date;
                std::cout << "Enter Patient's Name: ";
                std::cin >> patientName;
                std::cout << "Enter Doctor's Name: ";
                std::cin >> doctorName;
                std::cout << "Enter Appointment Date (YYYY-MM-DD): ";
                std::cin >> date;

                // Find doctor and patient
               Doctor selectedDoctor("", "", "", std::vector<std::string>());
                for (std::vector<Doctor>::const_iterator it = hospital.doctors.begin(); it != hospital.doctors.end(); ++it) {
                    if (it->name == doctorName) {
                        selectedDoctor = *it;
                        break;
                    }
                }

                Patient selectedPatient("", 0, "");
                for (std::vector<Patient>::const_iterator it = hospital.patients.begin(); it != hospital.patients.end(); ++it) {
                    if (it->name == patientName) {
                        selectedPatient = *it;
                        break;
                    }
                }

                if (selectedDoctor.name != "" && selectedPatient.name != "") {
                    hospital.scheduleAppointment(selectedPatient, selectedDoctor, date);
                    std::cout << "Appointment scheduled successfully!\n";
                } else {
                    std::cout << "Doctor or patient not found. Please check the names and try again.\n";
                }
                break;
            }
            case 4: {
                hospital.displayAppointments();
                break;
            }
            case 5: {
                int totalWards = 0;
                int reservedWards = 0;

                for (std::vector<Ward>::const_iterator it = hospital.wards.begin(); it != hospital.wards.end(); ++it) {
                    totalWards += it->total;
                    reservedWards += it->reserved;
                }

                std::cout << "Total Wards: " << totalWards << "\n";
                std::cout << "Reserved Wards: " << reservedWards << "\n";
                std::cout << "Free Wards: " << totalWards - reservedWards << "\n";
                break;
            }
            case 6: {
                std::string shift, day;
                std::cout << "Enter Shift (morning/night): ";
                std::cin >> shift;
                std::cout << "Enter Day (if applicable): ";
                std::cin >> day;
                hospital.displayAvailableDoctors(shift, day);
                break;
            }
            case 7: {
                std::string patientName, medicine;
                std::cout << "Enter Patient's Name: ";
                std::cin >> patientName;
                std::cout << "Enter Prescribed Medicine: ";
                std::cin >> medicine;

                // Find patient
                for (std::vector<Patient>::iterator it = hospital.patients.begin(); it != hospital.patients.end(); ++it) {
                    if (it->name == patientName) {
                        hospital.prescribeMedicine(*it, medicine);
                        break;
                    }
                }
                break;
            }
            case 8: {
                 // Assign Ward to Patient
                std::string patientName;
                std::cout << "Enter Patient's Name: ";
                std::cin >> patientName;

                // Find patient
                for (std::vector<Patient>::iterator it = hospital.patients.begin(); it != hospital.patients.end(); ++it) {
                    if (it->name == patientName) {
                        hospital.assignWardToPatient(*it);
                        break;
                    }
                }
                hospital.getWardInfo(); // Display updated ward information
                break;
                
            }
            case 9: {
                // Discharge Patient from Ward
                std::string patientName;
                std::cout << "Enter Patient's Name: ";
                std::cin >> patientName;

                // Find patient
                for (std::vector<Patient>::iterator it = hospital.patients.begin(); it != hospital.patients.end(); ++it) {
                    if (it->name == patientName) {
                        hospital.dischargePatientFromWard(*it);
                        break;
                    }
                }
                break;
            }
            case 0: {
                std::cout << "Exiting Hospital Management System. Goodbye!\n";
                break;
            }
            default:
                std::cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 0);

    return 0;
}
