def calculate_priority(waiting_time, estimated_run_time):
    return 1 + waiting_time / estimated_run_time

# Step 1: Input the number of processes
num_processes = int(input("Enter the number of processes: "))

# Step 2: Input the arrival time, estimated run time, and priority for each process
processes = []
for i in range(num_processes):
    arrival_time = int(input("Enter the arrival time for process {}: ".format(i+1)))
    estimated_run_time = int(input("Enter the estimated run time for process {}: ".format(i+1)))
    priority = calculate_priority(0, estimated_run_time)
    processes.append({
        "id": i+1,
        "arrival_time": arrival_time,
        "estimated_run_time": estimated_run_time,
        "priority": priority,
        "remaining_time": estimated_run_time,
        "waiting_time": 0
    })

# Step 3: Sort the processes based on priority
processes = sorted(processes, key=lambda p: p["priority"], reverse=True)

# Step 4: Initialize waiting time for each process to zero
for p in processes:
    p["waiting_time"] = 0

# Step 5: Run the scheduling algorithm
current_time = 0
completed_processes = []
gantt_chart = []
while len(completed_processes) < num_processes:
    # Select the process with the highest priority
    selected_process = processes[0]
    selected_index = 0
    # Check if the process has arrived
    if selected_process["arrival_time"] > current_time:
        current_time += 1
        continue
    # Execute the process until completion
    while selected_process["remaining_time"] > 0:
        selected_process["remaining_time"] -= 1
        current_time += 1
        gantt_chart.append(selected_process["id"])
    # Update the waiting time of the remaining processes
    for i in range(1, len(processes)):
        p = processes[i]
        if p["arrival_time"] <= current_time and p not in completed_processes:
            p["waiting_time"] += selected_process["estimated_run_time"]
            p["priority"] = calculate_priority(p["waiting_time"], p["estimated_run_time"])
    # Mark the process as completed
    completed_processes.append(selected_process)
    # Sort the remaining processes based on priority
    processes.pop(selected_index)
    processes = sorted(processes, key=lambda p: p["priority"], reverse=True)

# Step 6: Compute the average waiting time
total_waiting_time = sum([p["waiting_time"] for p in completed_processes])
average_waiting_time = total_waiting_time / num_processes

# Step 7: Display the results
print("\nProcess\tArrival Time\tEstimated Run Time\tWaiting Time")
for p in completed_processes:
    print("{}\t\t{}\t\t{}\t\t{}".format(p["id"], p["arrival_time"], p["estimated_run_time"], p["waiting_time"]))

print("\nAverage Waiting Time: {:.2f}".format(average_waiting_time))

# Display the Gantt chart
print("\nGantt Chart:")
for i in range(len(gantt_chart)):
    if i == 0 or gantt_chart[i] != gantt_chart[i-1]:
        print("|", end="")
    print("__", end="")
    if i == len(gantt_chart)-1:
        print("|", end="")
print("\n", end="")
for i in range(len(gantt_chart)):
    if i == 0 or gantt_chart[i] != gantt_chart[i-1]:
        print("|", end="")
    print("P{}".format(gantt_chart[i]), end="")
    if i == len(gantt_chart)-1:
        print("|", end="")
print("\n", end="")
print(len(gantt_chart))
for i in range(len(gantt_chart)):
    if i == 0 or gantt_chart[i] != gantt_chart[i-1]:
        print("{:2d}".format(completed_processes[gantt_chart[i]-1]["arrival_time"]), end="")
    print(" ", end="")
    if i == len(gantt_chart)-1:
        print(completed_processes[gantt_chart[i]-1]["arrival_time"] + completed_processes[gantt_chart[i]-1]["estimated_run_time"], end="")
print("\n")
