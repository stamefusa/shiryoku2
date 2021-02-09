<template>
  <section>
    <b-button @click="clickMe('a')">0.1</b-button>
    <b-button @click="clickMe('b')">0.5</b-button>
    <b-button @click="clickMe('c')">1.0</b-button>
    <b-button @click="clickMe('d')">2.0</b-button>
  </section>
</template>

<script>
export default{
  methods: {
    async clickMe(value) {
      this.$buefy.notification.open('Recognized- started.' + value)
      if (['a', 'b', 'c', 'd'].indexOf(value) != -1) {
        this.$axios.$get('http://localhost:8080/api/'+value);
      }

      const SpeechRecognition =
        window.webkitSpeechRecognition || window.SpeechRecognition
      const recognition = new SpeechRecognition()

      recognition.onresult = (e) => {
        const input = e.results[0][0].transcript
        this.$buefy.notification.open(input)

        if (input == "上") {
          this.$axios.$get('http://localhost:8080/api/0')
        } else if (input == "右上") {
          this.$axios.$get('http://localhost:8080/api/1')
        } else if (input == "右") {
          this.$axios.$get('http://localhost:8080/api/2')
        } else if (input == "右下") {
          this.$axios.$get('http://localhost:8080/api/3')
        } else if (input == "下") {
          this.$axios.$get('http://localhost:8080/api/4')
        }
      }

      recognition.onend = (e) => {
        this.$buefy.notification.open('Recognized ended.')
      }

      recognition.start()
    },
  },
}
</script>
