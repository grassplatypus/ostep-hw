import subprocess
import matplotlib.pyplot as plt

trials = input("How many trials: ")
pages = 1
hist_pages = []
hist_times = []
for i in range(int(trials)):
    print("Accessing " + str(pages) + " pages: ", end='')
    result = subprocess.run(["./tlb", trials, str(pages)],
                            text=True, stdout=subprocess.PIPE)
    print(result.stdout, "ns")
    hist_pages.append(pages)
    hist_times.append(int(result.stdout) / pages)
    pages *= 2

plt.figure(figsize=(10, 10))
plt.plot(hist_pages, hist_times, marker='o', color='orange')
plt.xscale('log')
plt.xticks(hist_pages, [str(i) for i in hist_pages], rotation=45, fontsize=10)
plt.minorticks_off()
plt.grid(True, which='major', axis='both', linestyle='-',
         linewidth=0.5, color='lightgrey')
plt.xlabel('Number Of Pages')
plt.ylabel('Time Per Access (ns)')
plt.title('TLB Size Measurement')
plt.tight_layout()
plt.savefig("graph.png")
plt.show()