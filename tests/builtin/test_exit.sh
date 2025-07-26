#!/bin/bash

# Colors
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
MAGENTA='\033[0;35m'
CYAN='\033[0;36m'
NC='\033[0m' # No Color

# Counters
PASSED=0
TOTAL=0

# Function to run a test
run_test() {
    local test_name="$1"
    local command="$2"
    
    echo -e "\n${MAGENTA}=== Testing: $test_name ===${NC}"
    echo -e "${BLUE}Command: $command${NC}"
    
    # Run with minishell
    echo "$command" | ./minishell 2>/dev/null
    minishell_exit=$?
    
    # Run with bash
    echo "$command" | bash 2>/dev/null
    bash_exit=$?
    
    echo -e "${YELLOW}Exit codes:${NC}"
    echo "  Minishell: $minishell_exit"
    echo "  Bash:      $bash_exit"
    
    if [ $minishell_exit -eq $bash_exit ]; then
        echo -e "${GREEN}✓ PASS${NC}"
        PASSED=$((PASSED + 1))
    else
        echo -e "${RED}✗ FAIL${NC}"
    fi
    
    TOTAL=$((TOTAL + 1))
}

# Function to run interactive test (for testing with actual shell prompt)
run_interactive_test() {
    local test_name="$1"
    local command="$2"
    
    echo -e "\n${MAGENTA}=== Interactive Test: $test_name ===${NC}"
    echo -e "${BLUE}Command: $command${NC}"
    
    # Create temporary files for outputs
    minishell_tmp=$(mktemp)
    bash_tmp=$(mktemp)
    
    # Test minishell
    echo "$command" > "$minishell_tmp"
    ./minishell < "$minishell_tmp" >/dev/null 2>&1
    minishell_exit=$?
    
    # Test bash  
    echo "$command" > "$bash_tmp"
    bash < "$bash_tmp" >/dev/null 2>&1
    bash_exit=$?
    
    echo -e "${YELLOW}Exit codes:${NC}"
    echo "  Minishell: $minishell_exit"
    echo "  Bash:      $bash_exit"
    
    if [ $minishell_exit -eq $bash_exit ]; then
        echo -e "${GREEN}✓ PASS${NC}"
        PASSED=$((PASSED + 1))
    else
        echo -e "${RED}✗ FAIL${NC}"
    fi
    
    TOTAL=$((TOTAL + 1))
    
    # Clean up
    rm -f "$minishell_tmp" "$bash_tmp"
}

# Main function
main() {
    echo -e "${CYAN}=== MINISHELL EXIT TESTER ===${NC}"
    echo "Comparing minishell exit behavior with bash"
    
    # Check if minishell exists
    if [ ! -f "./minishell" ]; then
        echo -e "${RED}Error: ./minishell not found. Please compile first.${NC}"
        exit 1
    fi
    
    # Check if we're in the right directory
    if [ ! -d "tests" ]; then
        echo -e "${YELLOW}Warning: 'tests' directory not found. Make sure you're in the project root.${NC}"
    fi
    
    # Test cases
    echo -e "\n${CYAN}Running basic exit tests...${NC}"
    
    run_interactive_test "exit" "exit"
    run_interactive_test "exit 0" "exit 0"
    run_interactive_test "exit 1" "exit 1"
    run_interactive_test "exit 42" "exit 42"
    run_interactive_test "exit 255" "exit 255"
    run_interactive_test "exit 256" "exit 256"
    run_interactive_test "exit -1" "exit -1"
    run_interactive_test "exit +42" "exit +42"
    run_interactive_test "exit -42" "exit -42"
    
    echo -e "\n${CYAN}Testing edge cases...${NC}"
    
    run_interactive_test "exit with string" "exit abc"
    run_interactive_test "exit multiple args" "exit 1 2"
    run_interactive_test "exit empty string" "exit ''"
    run_interactive_test "exit double quotes" 'exit ""'
    run_interactive_test "exit very large number" "exit 999999999999999999999"
    run_interactive_test "exit octal" "exit 007"
    run_interactive_test "exit with spaces" "exit   42   "
    
    # Summary
    echo -e "\n${CYAN}=== SUMMARY ===${NC}"
    echo "Passed: $PASSED/$TOTAL"
    
    if [ $PASSED -eq $TOTAL ]; then
        echo -e "${GREEN}All tests passed! 🎉${NC}"
        exit 0
    else
        echo -e "${RED}Some tests failed. 😞${NC}"
        exit 1
    fi
}

# Run if script is executed directly
if [ "${BASH_SOURCE[0]}" == "${0}" ]; then
    main "$@"
fi
